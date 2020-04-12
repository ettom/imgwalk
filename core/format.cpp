#include "format.h"

#include "core.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <iomanip>
#include <optional>
#include <string>

// some compile-time computation just for fun
// should make it easy to change the formatting if needed
enum columns { date, camera_model, path, number_of_columns };
constexpr const char* column_headers[] {"Date", "Camera model", "Path"};

static_assert(sizeof(column_headers) / sizeof(char*) == number_of_columns, "Sizes don't match");

constexpr auto column_header_widths = [] {
	std::array<size_t, number_of_columns> a {};

	for (size_t i = 0; i < number_of_columns; ++i) {
		a[i] = std::char_traits<char>::length(column_headers[i]);
	}

	return a;
}();

constexpr inline size_t column_separator_width {2};

size_t find_max_camera_model_length(const std::vector<ImgFile>& files)
{
	return std::max_element(files.begin(), files.end(),
				[](const ImgFile& a, const ImgFile& b) {
					return a.camera_model.value_or("").length()
					       < b.camera_model.value_or("").length();
				})
		->camera_model.value_or("")
		.length();
}

std::ostringstream format_results(const std::vector<ImgFile>& files)
{
	if (files.empty()) {
		return {};
	}

	// the column header might be longer than the longest camera model
	const size_t max_camera_model_length {
		std::max(find_max_camera_model_length(files), column_header_widths[columns::camera_model])};

	std::ostringstream ss;
	auto format_row = [&](const std::vector<std::string>& row) {
		ss << std::left << std::setw(date_width + column_separator_width) << row.at(columns::date)
		   << std::setw(static_cast<int>(max_camera_model_length + column_separator_width))
		   << row.at(columns::camera_model) << row.at(columns::path) << std::endl;
	};

	format_row(std::vector<std::string>(column_headers, column_headers + number_of_columns));
	for (const auto& imgfile : files) {
		const std::vector<std::string> row {imgfile.capture_date.value_or(""), //
						    imgfile.camera_model.value_or(""), //
						    std::string(imgfile.absolute_path)};
		format_row(row);
	}

	return ss;
}
