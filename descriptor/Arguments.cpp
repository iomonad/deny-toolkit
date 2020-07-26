//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#include <map>
#include <iostream>
#include <unistd.h>
#include <cstdlib>

#include "Arguments.hpp"

ArgsParser::ArgsParser(const char *argv[], int argc) {
    int c;

    while((c = getopt(argc, (char**)argv, "i:o:")) != -1) {
	switch(c) {
	case 'i':
	    if (optarg)
		argmap["i"] = optarg;
	    break;
	case 'o':
	    if (optarg)
		argmap["o"] = optarg;
	    break;
	}
    }
}

std::string ArgsParser::retrieve(std::string flag) {
    return argmap[flag];
}
