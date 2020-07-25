//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#include <memory>
#include <cstdlib>
#include <iostream>

#include "Arguments.hpp"
#include "Descriptor.hpp"

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
	auto input = make_shared<string>(args->retrieve("i"));
	auto output = make_shared<string>(args->retrieve("o"));

	if (!input->c_str() || !*output->c_str())
		print_usage_die(argv[0]);

	// Activity Manager
	auto descriptor = make_shared<Descriptor>(input->c_str());

	try {
		descriptor->start_activity();
	} catch (const std::exception& ex) {
		cerr << "Something went wrong: " << ex.what() << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
