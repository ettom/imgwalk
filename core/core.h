#pragma once
#include <filesystem>
#include <optional>
#include <string>
#include <vector>

constexpr inline const char* image_extensions[] {".jpg", ".jpeg", ".jpe", ".jif", ".jfif", ".jfi"};
constexpr inline size_t date_width {10};

struct ImgFile {
	std::filesystem::path filename;
	std::filesystem::path absolute_path;

	bool exif_found = true;

	std::optional<std::string> capture_date;
	std::optional<std::string> camera_model;
};

struct FilterRules {
	bool ignore_case = false;
	bool ignore_files_without_exif = true;

	std::optional<std::string> filename;
	std::optional<std::string> capture_date;
	std::optional<std::string> camera_model;
};
