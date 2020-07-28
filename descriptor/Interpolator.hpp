//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <string>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class Interpolator {
private:
    std::ofstream target;
public:
    Interpolator(std::string path, bitting_t bitting);
    ~Interpolator();
    void pack();
};

#endif /* INTERPOLATOR_H */
