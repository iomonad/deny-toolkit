//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#ifndef KEY_H
#define KEY_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

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

#endif /* KEY_H */
