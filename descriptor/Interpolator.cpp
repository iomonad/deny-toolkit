//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#include <string>
#include <fstream>
#include <iostream>

#include "Commons.hpp"
#include "Interpolator.hpp"

Interpolator::Interpolator(std::string path, bitting_t bitting)
    : _bitting(bitting) {
    target.open(path);

    if (!target.good()) {
	throw std::runtime_error("File Error !");
    }
}

Interpolator::~Interpolator() {
    target.close();
}

//
// @desc Regularize coord to genese (first)
//       point, for post interpretation consistency
//

void Interpolator::regularize_bitting(std::function<void(std::string)> failure,
			std::function<void()> success) {

    cv::Point genese = _bitting.front();

    // Maybe logic should be hardened ?
    for (auto &variation : _bitting) {
	variation.x -= genese.x;
    }
}

//
// @desc Lambda throw helper, maybe useful to add
//       some cleanup when error occur to gracefuly
//       exit.
//

static void raise_exception(std::string what) {
    throw std::runtime_error(what);
}

void Interpolator::pack(int flow) {
    static constexpr void (Interpolator::*flow_func[])
	(std::function<void(std::string)>,
	 std::function<void()>) = {
	&Interpolator::regularize_bitting,
    };
    static constexpr int n_func =
        sizeof(flow_func) / sizeof(*flow_func);

    if (flow < n_func) {
	return (this->*flow_func[flow])(raise_exception, [=]() {
	    return (this->pack(flow + 1));
	});
    } else {
	// Cleanup
	return ;
    }
}
