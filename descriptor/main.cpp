//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#include <memory>
#include <cstdlib>
#include <iostream>

#include "Arguments.hpp"

using namespace std;

static inline void
print_usage_die(const string av) {
	cerr << "Usage: " << av
	     << " -i <input image> -o <output file>]" << endl;
	exit(EXIT_FAILURE);
}

int
main(int argc, const char *argv[]) {
	auto args = make_shared<ArgsParser>(argv, argc);
	auto input = make_shared<std::string>(args->retrieve("i"));
	auto output = make_shared<std::string>(args->retrieve("o"));

	if (!input->c_str() || !*output->c_str())
		print_usage_die(argv[0]);
	return EXIT_SUCCESS;
}
