//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#include <string>
#include <fstream>
#include <iostream>

#include "../Commons.hpp"
#include "Interpolator.hpp"

Interpolator::Interpolator(std::string path, bitting_t bitting,
			   std::vector<cv::Rect> levers)
	: _bitting(bitting), _levers(levers) {
    target.open(path);

    keyinfo.MAGIC = 0xde57de57;
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
    int ymin = genese.y;
    shared_genese = genese;

    // Maybe logic should be hardened ?
    for (auto &variation : _bitting) {
	variation.x -= genese.x;
	if (variation.y < ymin) {
	    ymin = variation.y;
	}
    }
    for (auto &variation : _bitting) {
	variation.y -= ymin;
    }
    return success();
}

void Interpolator::regularize_levers(std::function<void(std::string)> failure,
				     std::function<void()> success) {
	cv::Point genese = shared_genese;//_levers.front();
	int ymin = genese.y;

	for (auto &lev: _levers) {
		lev.x -= genese.x;
		if (lev.y < ymin) {
			ymin = lev.y;
		}
	}
	for (auto &lev : _levers) {
		lev.y -= ymin;
	}
	return success();
}

void Interpolator::craft_file(std::function<void(std::string)> failure,
			      std::function<void()> success) {

    std::string combiname;

    if (!target.good()) {
	// Unsure no changes since fd opening
	return failure(__func__);
    }

    std::cout << "Enter combinaison name: ";
    std::cin >> combiname;
    std::cout << "Enter combinaison type {1-2-3}:";
    std::cin >> keyinfo.combinaison_type;
    std::cout << "Protected bitting ? [0/1]:";
    std::cin >> keyinfo.protected_type;

    strncpy(keyinfo.name, combiname.c_str(), 32);
    // Pack Header
    target.write((char *) &keyinfo, sizeof(struct KeyHeader));
    // Pack Levers
    for (auto &l : _levers) {
        struct KeyLever lev = {
	    (unsigned short)l.x,
	    (unsigned short)l.y,
	    (unsigned short)l.width,
	    (unsigned short)l.height
	};
	target.write((char*)&lev, sizeof(struct KeyLever));
	std::cout << "L "<< l << std::endl;
    }
    // Back Body
    for (auto &b : _bitting) {
	struct KeyBody body = {
	    (unsigned short)b.x,
	    (unsigned short)b.y
	};
	std::cout << "B "<< b << std::endl;
	target.write((char*)&body, sizeof(struct KeyBody));
    }
    std::cout << "Succesfully saved key '" << combiname << "'" << std::endl;
    return success();
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
	&Interpolator::regularize_levers,
	&Interpolator::craft_file,
    };
    static constexpr int n_func =
        sizeof(flow_func) / sizeof(*flow_func);

    if (flow < n_func) {
	return (this->*flow_func[flow])(raise_exception, [=]() {
	    return (this->pack(flow + 1));
	});
    } else {
	target.close();
	return ;
    }
}
