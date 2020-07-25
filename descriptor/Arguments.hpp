//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

#include <map>
#include <cstdlib>
#include <iostream>

class ArgsParser {
private:
	// Internal argument map
	std::map<std::string, std::string> argmap;
public:
	std::string retrieve(std::string flag);
	ArgsParser(const char *argv[], int argc);
};

#endif /* ARGUMENTS_HPP */
