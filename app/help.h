#pragma once

#include <iostream>
#include <string>

void print_help()
{
	const std::string help = R"(Usage:
imgwalk [OPTION(S)] [FILE(S)]

-f PATTERN    show files whose names (extension included) match the PATTERN
              wildcards allowed in the PATTERN
-c PATTERN    show files whose camera model matches the PATTERN
              wildcards allowed in the PATTERN
-d PATTERN    show files whose capture date exactly matches the PATTERN
              date is in the format of "YYYY:MM:DD"

-a            display all matching files, even if they don't have any Exif data
-i            ignore case distinctions in PATTERNS
-h            display this help text and exit)";
	std::cout << help << std::endl;
}
