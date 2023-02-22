#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>

int main(int argc, char** argv)
{
	if (argc < 2) {
		fprintf(stderr, "Usage: cat <path>\n");
		exit(1);
	}
	
	std::string path(argv[1]);

	return 0;
}
