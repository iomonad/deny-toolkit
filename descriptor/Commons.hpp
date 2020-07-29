//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#ifndef COMMONS_H
#define COMMONS_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

// Bitting Data Structure
typedef std::vector<cv::Point> bitting_t;

// Key descriptor
#pragma pack(push, 1)
struct Key {
    std::size_t MAGIC;
};
#pragma pack(pop)

#endif /* COMMONS_H */
