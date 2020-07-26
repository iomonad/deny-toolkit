//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#ifndef DESCRIPTOR_HPP
#define DESCRIPTOR_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

# define DESCRIPTOR_WIN_NAME "image"

//
// @description Descriptor Class.
//     Manage the lifecycle of user
//     input on the given image.
// @args fname Input image path
//

class Descriptor {
private:
    cv::Mat image;
    static void mousekb(int ev, int x, int y, int f, void* data);
    // Flow Components
    void initial_closeup(std::function<void(std::string)> failure,
			 std::function<void()> success);
    void combinaison_capture(std::function<void(std::string)> failure,
			     std::function<void()> success);
public:
    Descriptor(std::string fname);
    ~Descriptor();
    void start_activity(int flow = 0);
};


#endif	/* DESCRIPTOR_HPP */
