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
// @desc Mouse Event Callback logic
//

void Descriptor::mousekb(int ev, int x, int y,
			 int f, void* data) {
    switch (ev) {
    case cv::EVENT_LBUTTONDOWN:
	std::cout << "Left button of the mouse is clicked - position ("
		  << x << ", " << y << ")" << std::endl;
	break;
    }
}

void Descriptor::initial_closeup(std::function<void(std::string)> failure,
				 std::function<void()> success) {
    char k;

    cv::namedWindow(DESCRIPTOR_WIN_NAME, cv::WINDOW_AUTOSIZE | cv::WINDOW_GUI_NORMAL);
    cv::setMouseCallback(DESCRIPTOR_WIN_NAME, mousekb);
    cv::imshow(DESCRIPTOR_WIN_NAME, image);
    for (;;) {
	cv::imshow(DESCRIPTOR_WIN_NAME, image);
	k = cv::waitKey(0);
	if (k == 'r')
	    cv::rotate(image, image, cv::ROTATE_90_CLOCKWISE);
	if (k == 'c')
	    cv::rotate(image, image, -10);
	if (k == 'f')
	    cv::flip(image, image, 1);
	if (k == 'F')
	    cv::flip(image, image, 0);
	if (k == 'q')
	    break;
    }
    return success();
}

void Descriptor::combinaison_capture(std::function<void(std::string)> failure,
				     std::function<void()> success) {
    char k;

    cv::namedWindow(DESCRIPTOR_WIN_NAME, cv::WINDOW_AUTOSIZE | cv::WINDOW_GUI_NORMAL);
    cv::setMouseCallback(DESCRIPTOR_WIN_NAME, mousekb);
    cv::imshow(DESCRIPTOR_WIN_NAME, image);
    for (;;) {
	cv::imshow(DESCRIPTOR_WIN_NAME, image);
	k = cv::waitKey(0);
	if (k == 'r')
	    cv::rotate(image, image, cv::ROTATE_90_CLOCKWISE);
	if (k == 'f')
	    cv::flip(image, image, 1);
	if (k == 'F')
	    cv::flip(image, image, 0);
	if (k == 'q')
	    break;
    }
    return success();
}

//
// @desc Lambda throw helper, maybe useful to add
//       some cleanup when error occur to gracefuly
//       exit.
//

static void raise_exception(std::string what) {
    throw std::runtime_error(what);
}

//
// @desc Start Activity flow
//

void Descriptor::start_activity(int flow) {
    static constexpr void (Descriptor::*flow_func[])
	(std::function<void(std::string)>,
	 std::function<void()>) = {
	&Descriptor::initial_closeup,
	&Descriptor::combinaison_capture,
    };
    static constexpr int n_func =
        sizeof(flow_func) / sizeof(*flow_func);

    if (flow < n_func) {
	return (this->*flow_func[flow])(raise_exception, [=]() {
	    return (this->start_activity(flow + 1));
	});
    } else {
	// Maybe cleanup support ?
	return ;
    }
}
