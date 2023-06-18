#include "skutilflagparser.hpp"
#include <stdlib.h>
#include <iostream>

void testFunc(...)
{
	std::cout << "This is from a custom flag" << std::endl;
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
