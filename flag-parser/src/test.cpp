#include "skutilflagparser.hpp"
#include <stdlib.h>
#include <iostream>
#include <cstdarg>

void testFunc(int count, ...)
{
	std::cout << "This is from a custom flag" << std::endl;

    // std::va_list list;
    // va_start(list, count);
    // std::cout << count << std::endl;

    // // std::cout << va_arg(list, char*) << std::endl;

    // va_end(list);
}

int main(int argc, char** argv) 
{
	// Initialize flags
	SKUTIL::SK_VEC<SKUTIL::Flag> flags {
		{
			't',
			"test",
			"Test function",
			testFunc
		},
	};

	SKUTIL::FlagParser parser = SKUTIL::FlagParser(&flags);

	if (argc < 2)
		std::cout << "No Flags Passed\n";
	else
		parser.ParseFlags(argc, argv);

	return 0;
}
