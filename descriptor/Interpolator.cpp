//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#include <string>
#include <fstream>

#include "Commons.hpp"
#include "Interpolator.hpp"

Interpolator::Interpolator(std::string path, bitting_t bitting) {
    target.open(path);

    if (!target.good()) {
	throw std::runtime_error("File Error !");
    }
}

Interpolator::~Interpolator() {
    target.close();
}

void Interpolator::pack() {
    return ;
}
