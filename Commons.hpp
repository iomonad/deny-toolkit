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

// Key descriptor Header
#pragma pack(push, 1)
struct KeyHeader {
    std::size_t MAGIC;
    char name[32];
    unsigned short protected_type;
    unsigned short combinaison_type;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct KeyLever {
	unsigned short x;
	unsigned short y;
	unsigned short width;
	unsigned short height;
};
#pragma pack(pop)

// Key Descriptor Body
#pragma pack(push, 1)
struct KeyBody {
    unsigned short x;
    unsigned short y;
};
#pragma pack(pop)

// Complete definition (highlevel)
struct Key {
	struct KeyHeader header;
	std::vector<cv::Rect> levers;
	std::vector<cv::Point> bitting;
};

#endif /* COMMONS_H */
