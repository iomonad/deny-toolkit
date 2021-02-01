//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <string>
#include <fstream>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../Commons.hpp"

class Interpolator {
private:
    std::ofstream target;
    bitting_t _bitting;
    std::vector<cv::Rect> _levers;
    KeyHeader keyinfo;

    // Flow Components
    void regularize_bitting(std::function<void(std::string)> failure,
			    std::function<void()> success);
    void regularize_levers(std::function<void(std::string)> failure,
			   std::function<void()> success);
    void craft_file(std::function<void(std::string)> failure,
		    std::function<void()> success);
public:
    Interpolator(std::string path, bitting_t bitting,
		 std::vector<cv::Rect> levers);
    ~Interpolator();
    void pack(int flow = 0);
};

#endif /* INTERPOLATOR_H */
