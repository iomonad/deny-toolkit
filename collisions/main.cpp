//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#include <cstdlib>
#include <iostream>

#include "Superposer.hpp"

static int usage(void) {
	std::cout << "You should provide at least one combainaison."
		  << std::endl;
	return 1;
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		return usage();
	}
	std::vector<std::string> all_args(argv, argv + argc);
	all_args.erase(all_args.begin()); // Remove argv1
	auto superposer = std::make_shared<Superposer>(all_args);
	try {
		superposer->compute();
	} catch (const std::exception& ex) {
		std::cerr << "Something went wrong: " << ex.what() << std::endl;
		return EXIT_FAILURE;
	}
	return 0;
}
