#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

int main(int argc, char** argv)
{
	if (argc < 2) {
		fprintf(stderr, "Usage: cat <path>\n");
		exit(1);
	}
	
	std::ifstream file;
	std::string path(argv[1]);
	file.open(path);
	if (file.fail())
		return -1;

	std::string line;	
	if (!file.is_open())
		return -1;

	while (std::getline(file, line)) {
		std::cout << line << "\n";
	}

	return 0;
}
