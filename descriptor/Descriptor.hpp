//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#ifndef DESCRIPTOR_HPP
#define DESCRIPTOR_HPP

#include <list>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Commons.hpp"

# define DESCRIPTOR_WIN_NAME "image"

//
// @description Descriptor Class.
//     Manage the lifecycle of user
//     input on the given image.
// @args fname Input image path
//

class Descriptor {
private:
    // Bitting
    bitting_t bitting;
    std::list<cv::Rect> levers;

    // Flow Components
    void initial_closeup(std::function<void(std::string)> failure,
			 std::function<void()> success);
    void combinaison_capture(std::function<void(std::string)> failure,
			     std::function<void()> success);
    void bitting_preview(std::function<void(std::string)> failure,
			 std::function<void()> success);
    void levers_disposition(std::function<void(std::string)> failure,
			   std::function<void()> success);
public:
    Descriptor(std::string fname);
    ~Descriptor();
    void start_activity(int flow = 0);
    bitting_t get_bitting();
    std::list<cv::Rect> get_levers();
};

// PLEASE NEVER DO THIS

namespace DescriptorScope {
    static cv::Mat image;
    static cv::Mat image_stock;
}

#endif	/* DESCRIPTOR_HPP */
