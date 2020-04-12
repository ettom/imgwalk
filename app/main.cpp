#include "core.h"
#include "filter.h"
#include "format.h"
#include "help.h"
#include "search.h"

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include <unistd.h>

#define EXIT_ERROR 2

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
	FilterRules filter_rules {};
	int index, c;

	while ((c = getopt(argc, argv, "haif:d:c:")) != -1) {
		switch (c) {
		case 'f':
			filter_rules.filename = optarg;
			break;
		case 'c':
			filter_rules.camera_model = optarg;
			break;
		case 'd':
			filter_rules.capture_date = optarg;
			break;
		case 'i':
			filter_rules.ignore_case = true;
			break;
		case 'a':
			filter_rules.ignore_files_without_exif = false;
			break;
		case '?':
			print_help();
			return EXIT_FAILURE;
		case 'h':
			print_help();
			return EXIT_SUCCESS;
		default:
			abort();
		}
	}

	int exit_code = EXIT_SUCCESS;

	std::vector<fs::path> paths;

	for (index = optind; index < argc; index++) {
		char* path = argv[index];
		if (!fs::exists(path)) {
			std::cerr << path << ": no such file or directory" << std::endl;
			exit_code = EXIT_ERROR;
		} else {
			paths.emplace_back(path);
		}
	}

	if ((argc > optind) && paths.empty()) {
		// user provided some paths but none of them were valid
		return exit_code;
	}

	if (paths.empty()) {
		paths.push_back(fs::current_path());
	}

	std::vector<ImgFile> files;
	for (const auto& path : paths) {
		std::vector<ImgFile> tmp = find_images(path);
		files.insert(files.end(), tmp.begin(), tmp.end());
	}

	std::vector<ImgFile> filtered = filter_image_files(files, filter_rules);
	std::cout << format_results(filtered).str();

	return exit_code;
}
