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

Descriptor::~Descriptor() {
    //
    // TODO: Maybe try to find a smarter
    // way to free up memory ?
    //
    cv::destroyAllWindows();
}

//
// @desc Start Activity flow
//

void Descriptor::start_activity() {
    char k;

    cv::namedWindow(DESCRIPTOR_WIN_NAME, cv::WINDOW_GUI_EXPANDED);
    cv::imshow(DESCRIPTOR_WIN_NAME, image);
    for (;;) {
	cv::imshow(DESCRIPTOR_WIN_NAME, image);
	k = cv::waitKey(0);
	if (k == 'r') {
	    cv::rotate(image, image, cv::ROTATE_90_CLOCKWISE);
	}
	if (k == 'q') {
	    break;
	}
    }
}
