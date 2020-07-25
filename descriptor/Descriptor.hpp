//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#ifndef DESCRIPTOR_HPP
#define DESCRIPTOR_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

# define DESCRIPTOR_WIN_NAME "Dény Descriptor"

//
// @description Descriptor Class.
//     Manage the lifecycle of user
//     input on the given image.
// @args fname Input image path
//

class Descriptor {
private:
	cv::Mat image;
public:
	Descriptor(std::string fname);
	~Descriptor();
	void start_activity();
	
};


#endif	/* DESCRIPTOR_HPP */
