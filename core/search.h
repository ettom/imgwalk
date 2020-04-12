#pragma once
#include <filesystem>
#include <vector>

struct ImgFile;

std::vector<ImgFile> find_images(const std::filesystem::path& path);
