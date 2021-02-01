//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#ifndef SUPERPOSER_HPP
#define SUPERPOSER_HPP

#include <map>
#include <string>
#include <fstream>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../Commons.hpp"

class Superposer {
private:
	std::vector<std::ifstream*> fsw;
	// Highlevel unpacked keys
	std::vector<struct Key> keys;
	void unpack_files(std::function<void(std::string)> failure,
			  std::function<void()> success);
public:
	Superposer(std::vector<std::string> fpaths);
	~Superposer();
	void compute(int flow = 0);
};

#endif	// SUPERPOSER_HPP
