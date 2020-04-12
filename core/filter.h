#pragma once
#include <vector>

struct ImgFile;
struct FilterRules;

std::vector<ImgFile> filter_image_files(const std::vector<ImgFile>& input, const FilterRules& filtering_rules);
