#pragma once
#include <sstream>
#include <vector>

struct ImgFile;

std::ostringstream format_results(const std::vector<ImgFile>& files);
