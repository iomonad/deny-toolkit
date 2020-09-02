//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Key.hpp"

static int usage(char *argv[]) {
    std::cout << "Usage: " << argv[0]
	      << " <file bitting>" << std::endl;
    return EXIT_FAILURE;
}

int main(int argc, char *argv[]) {
    struct KeyHeader header;
    std::vector<KeyBody> body;
    std::ifstream input;

    if (argc != 2) {
	return usage(argv);
    }
    input.open(argv[1]);
    if (!input.good()) {
	std::cout << "Failed opening " << argv[1];
	return EXIT_FAILURE;
    }
    input.read((char*)&header, sizeof(struct KeyHeader));
    if (header.MAGIC != 0xde57de57) {
	std::cerr << "Corruputed file, Exiting." << std::endl;
	input.close();
	exit(EXIT_FAILURE);
    }
    input.close();
    return EXIT_SUCCESS;
}
