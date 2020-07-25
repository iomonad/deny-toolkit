//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#ifndef DESCRIPTOR_HPP
#define DESCRIPTOR_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class Descriptor {
private:
	Mat image;
public:
	Descriptor(const std::string fname);
};


#endif	/* DESCRIPTOR_HPP */
