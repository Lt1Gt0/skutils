#include "skutilflagparser.hpp"
#include <stdlib.h>
#include <iostream>
#include <cstdarg>

void testFunc(OPT int inputCount, OPT char** inputVals)
{
	std::cout << "Input Count: " << inputCount << std::endl;

	for (int i = 0; i < inputCount; i++) {
		std::cout << inputVals[i] << "\n";
	}
}

int main(int argc, char** argv) 
{
	// Initialize flags
	SKUTIL::SK_VEC<SKUTIL::Flag> flags {
		{
			't',
			"test",
			"Test function",
			2,
			testFunc,
		},
	};

	SKUTIL::FlagParser parser = SKUTIL::FlagParser(&flags);

	if (argc < 2)
		std::cout << "No Flags Passed\n";
	else
		parser.ParseFlags(argc, argv);

	return 0;
}
