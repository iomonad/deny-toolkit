//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Descriptor.hpp"

Descriptor::Descriptor(std::string fname) {
	image = cv::imread(fname, cv::IMREAD_GRAYSCALE);

	if(!image.data) {
		throw std::runtime_error("Unable to load image.");
	}
}

//
// @desc Start Activity flow
//

void Descriptor::start_activity() {
	cv::namedWindow(DESCRIPTOR_WIN_NAME, cv::WINDOW_AUTOSIZE);
	cv::imshow(DESCRIPTOR_WIN_NAME, image);
	cv::waitKey(0);
}
