#include "skutilflagparser.hpp"
#include <stdlib.h>
#include <iostream>

int main(int argc, char** argv) 
{

	// Initialize flags
	SKUTIL::SK_VEC<SKUTIL::Flag> flags {
		{
			'h',
			"help",
			"Show help commands"
		}
	};

	SKUTIL::FlagParser parser = SKUTIL::FlagParser(&flags);

	if (argc < 2)
		std::cout << "No Flags Passed\n";
	//SKUTIL::FlagParser parser = new SKUTIL::FlagParser();
	

	return 0;
}
