#pragma once
#include <regex>
#include <string>

inline bool is_match(const std::string& text, const std::string& pattern, bool ignore_case = false)
{
	static const std::regex special_chars {R"([-[\]{}()+?.,\^$|#\s])"};

	// escape every occurrence of a special character
	std::string sanitized_pattern {std::regex_replace(pattern, special_chars, R"(\$&)")};

	// replace all * with .*
	sanitized_pattern = std::regex_replace(sanitized_pattern, std::regex("\\*"), ".*");

	auto rgx = ignore_case ? std::regex(sanitized_pattern, std::regex_constants::icase)
			       : std::regex(sanitized_pattern);

	return std::regex_match(text, rgx);
}
