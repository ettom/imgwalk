#include "filter.h"

#include "core.h"
#include "match.h"

#include <algorithm>
#include <filesystem>
#include <iterator>
#include <optional>
#include <string>

auto make_predicate(const FilterRules& filter)
{
	return [&](const ImgFile& img) {
		bool filename_matches = !filter.filename.has_value(); // if no value was provided, it always matches
		bool camera_model_matches = !filter.camera_model.has_value();
		bool capture_date_matches = !filter.capture_date.has_value();

		if (!img.exif_found && filter.ignore_files_without_exif) {
			return false;
		}

		// |= does not work as it isn't lazy
		filename_matches =
			filename_matches || (is_match(img.filename, filter.filename.value(), filter.ignore_case));

		camera_model_matches =
			camera_model_matches
			|| (img.camera_model.has_value()
			    && is_match(img.camera_model.value(), filter.camera_model.value(), filter.ignore_case));

		capture_date_matches =
			capture_date_matches
			|| (img.capture_date.has_value() && img.capture_date == filter.capture_date.value());

		return filename_matches && capture_date_matches && camera_model_matches;
	};
}

template <class T, typename Func>
std::vector<T> filter(const Func& pred, const std::vector<T>& input)
{
	std::vector<T> result;
	std::copy_if(input.begin(), input.end(), std::back_inserter(result), pred);
	return result;
}

std::vector<ImgFile> filter_image_files(const std::vector<ImgFile>& input, const FilterRules& filtering_rules)
{
	auto pred = make_predicate(filtering_rules);
	return filter<ImgFile, decltype(pred)>(pred, input);
}
