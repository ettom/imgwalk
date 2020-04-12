#include <iostream>
#include <cassert>

#include "match.h"

void test_wildcard_matching()
{
	assert(is_match("some_filename", "some*"));
	assert(is_match("some_filename", "some*name"));
	assert(is_match("some_filename", "so*fi*ame"));

	assert(!is_match("some_filename", "some*nam"));

	assert(is_match(".some_dotfile", ".so*"));
	assert(is_match(".some_dotfile", "*"));

	assert(is_match("käärid", "*äär*"));
	assert(is_match("nööp", "nööp"));
	assert(is_match("mõõdukas", "m*d*u*k*a*s"));

	assert(is_match("some_file_$[]^,£|\\s?_name", "some*name"));
	assert(is_match("some_file_$[]^,£|\\s?_name", "some*"));

	assert(is_match("SomeFileName", "some*", true));
	assert(is_match("SomeFileName", "*FILE*", true));
}

int main()
{
	std::cout << "Running tests..." << std::endl;
	test_wildcard_matching();
	std::cout << "If you're reading this, it means that all the tests passed." << std::endl;
	return 0;
}
