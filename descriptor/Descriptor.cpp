//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>

#include "Descriptor.hpp"

using namespace DescriptorScope;

Descriptor::Descriptor(std::string fname) {
    image = cv::imread(fname, cv::IMREAD_GRAYSCALE);

    // Deep Stock Copy
    image.copyTo(image_stock);
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
// @desc First step in the pipeline, properly setup
//       image orientation in order to have a nice constistency
//       for next step.
//

void Descriptor::initial_closeup(std::function<void(std::string)> failure,
				 std::function<void()> success) {
    char k;

    static std::tuple<cv::Point, cv::Point> closeup
	= std::make_tuple(cv::Point(0,0), cv::Point(0,0));

    cv::namedWindow(DESCRIPTOR_WIN_NAME, cv::WINDOW_AUTOSIZE | cv::WINDOW_GUI_NORMAL);
    cv::setMouseCallback(DESCRIPTOR_WIN_NAME, [](int ev, int x, int y, int f, void *data) {
        switch (ev) {
	case cv::EVENT_LBUTTONDOWN:
	    // Dummy click reset
	    image_stock.copyTo(image);
	    std::get<0>(closeup) = cv::Point(0, 0);
	    std::get<1>(closeup) = cv::Point(0, 0);
	    std::get<0>(closeup) = cv::Point(x, y);
	    break;
	case cv::EVENT_LBUTTONUP:
	    std::get<1>(closeup) = cv::Point(x, y);
	    break;
	}
	if (std::get<0>(closeup).x != 0 && std::get<0>(closeup).y != 0 &&
	    std::get<1>(closeup).x != 0 && std::get<1>(closeup).y != 0) {
	    // Draw Closeup
	    cv::rectangle(image, std::get<0>(closeup), std::get<1>(closeup),
			  cv::Scalar(0, 255, 0), 3);
	}
    });

    //
    // Important: Correct Key orientation should be done
    // before populating the key combinaison !
    //

    for (;;) {
	cv::imshow(DESCRIPTOR_WIN_NAME, image);
	k = cv::waitKey(100);
	if (k == 'r') {
	    cv::rotate(image, image, cv::ROTATE_90_CLOCKWISE);
	    image.copyTo(image_stock);
	}
	if (k == 'c') {
	    cv::rotate(image, image, -10);
	    image.copyTo(image_stock);
	}
	if (k == 'f') {
	    cv::flip(image, image, 1);
	    image.copyTo(image_stock);
	}
	if (k == 'F') {
	    cv::flip(image, image, 0);
	    image.copyTo(image_stock);
	}
        if (k == 0x20) {
	    // Only if closeup is setup
	    if (std::get<0>(closeup).x != 0 && std::get<0>(closeup).y != 0 &&
		std::get<1>(closeup).x != 0 && std::get<1>(closeup).y != 0) {
		cv::Rect roi(std::get<0>(closeup), std::get<1>(closeup));

		image = image(roi);
		break;
	    }
	}
    }
    return success();
}

//
// @desc Gather correct combinaison by placing dots
//       on combinaison edges.
//

void Descriptor::combinaison_capture(std::function<void(std::string)> failure,
				     std::function<void()> success) {
    char k;

    static std::vector<cv::Point> combinaison;

    cv::namedWindow(DESCRIPTOR_WIN_NAME, cv::WINDOW_AUTOSIZE | cv::WINDOW_GUI_NORMAL);
    cv::setMouseCallback(DESCRIPTOR_WIN_NAME, [](int ev, int x, int y, int f, void *data) {
        switch (ev) {
	case cv::EVENT_LBUTTONDOWN:
	    cv::Point select(x, y);

	    // @@ CONSISTENCY RULES @@
	    // NX Should never < than LX
	    // X Should be the same when Y Increment
	    // Y Should be the same when X Increment
	    //
	    if (combinaison.size() > 1) {
		cv::Point last = combinaison.back();

		if (select.x < last.x) {
		    // Select should be X Progressive
		    select.x = last.x;
		}

		cv::line(image, last, select, cv::Scalar(0, 254, 0), 2);
	    }
	    combinaison.push_back(select);
	    break;
	}
    });

    for (;;) {
	cv::imshow(DESCRIPTOR_WIN_NAME, image);
	k = cv::waitKey(100);
	if (k == 0x20)
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
	image.release();
	return ;
    }
}
