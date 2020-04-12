#include "search.h"

#include "core.h"

#include <libexif/exif-content.h>
#include <libexif/exif-data.h>
#include <libexif/exif-entry.h>
#include <libexif/exif-ifd.h>
#include <libexif/exif-tag.h>

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <iterator>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

namespace fs = std::filesystem;

inline bool is_image_file(const fs::path& path)
{
	return std::find(std::begin(image_extensions), std::end(image_extensions), path.extension().string())
	       != std::end(image_extensions);
}

std::optional<std::string> get_tag(const ExifData* d, ExifIfd ifd, ExifTag tag)
{
	// check if tag exists
	ExifEntry* entry = exif_content_get_entry(d->ifd[ifd], tag);
	if (!entry) {
		return {};
	}

	char buf[1024];

	// get the contents of the tag
	exif_entry_get_value(entry, buf, sizeof(buf));

	std::string result {buf};
	return result.empty() ? std::nullopt : std::optional<std::string>(result);
}

std::string_view format_capture_date(std::string_view datetime)
{
	// we only care about the date part
	return datetime.substr(0, date_width);
}

ImgFile make_imgfile(const fs::path& path)
{
	ImgFile imgfile;
	imgfile.absolute_path = fs::absolute(path);
	imgfile.filename = path.filename();

	ExifData* ed = exif_data_new_from_file(path.c_str());
	if (!ed) {
		imgfile.exif_found = false;
		return imgfile;
	}

	imgfile.capture_date = get_tag(ed, EXIF_IFD_EXIF, EXIF_TAG_DATE_TIME_ORIGINAL);
	imgfile.camera_model = get_tag(ed, EXIF_IFD_0, EXIF_TAG_MODEL);

	exif_data_unref(ed);

	bool date_has_value = imgfile.capture_date.has_value();
	if (date_has_value) {
		imgfile.capture_date = format_capture_date(imgfile.capture_date.value());
	}

	imgfile.exif_found = date_has_value || imgfile.camera_model.has_value();

	return imgfile;
}

std::vector<ImgFile> find_images(const fs::path& path)
{
	std::vector<ImgFile> imgfiles;
	if (fs::is_regular_file(path) && is_image_file(path)) {
		imgfiles.push_back(make_imgfile(path));
		return imgfiles;
	}

	std::error_code os_error;
	fs::recursive_directory_iterator walker {path, fs::directory_options::skip_permission_denied, os_error};
	auto last_path = path; // save the last directory before recursing into
			       // it to give a meaningful message in case of an os error

	auto it = fs::begin(walker);

	if (os_error) { // this means that we're already at the last item and
			// the loop won't be executed, but we still want to report the error
		std::cerr << "os error \"" << os_error << "\" in " << last_path << std::endl;
	}

	while (it != fs::end(walker)) {
		if (os_error) {
			std::cerr << "os error \"" << os_error << "\" in " << last_path << std::endl;
			it.disable_recursion_pending(); // disable recursion until the next increment
			it.pop();			// move the iterator one level up in the directory hierarchy
		} else {
			auto entry = *it;

			if (is_image_file(entry)) {
				imgfiles.push_back(make_imgfile(entry));
			}

			last_path = entry.path();
		}

		it.increment(os_error);
	}

	return imgfiles;
}
