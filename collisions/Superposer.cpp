//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#include <list>
#include <fstream>
#include <iostream>

#include "Superposer.hpp"

// Basic constructor, load files into
// fstream.

Superposer::Superposer(std::vector<std::string> fpaths) {
	for (const auto path: fpaths) {
		std::ifstream s;
		s.open(path);

		if (!s.good()) {
			s.close();
			for (const auto f: fsw)
				f->close();
			throw std::runtime_error("File " + path + " don't exists.");
		}
		// Warning: Pointers become invalid.
		// Be careful with object lifecycle
		fsw.push_back(&s);
		std::cout << "[OK]  Loaded " << path
			  << "." << std::endl;
	}
}

Superposer::~Superposer() {
	for ( auto f: fsw) {
		if (f->is_open()) {
			// To fix, segfault on free.
			// Maybe deleted before the destructor
			// is called ?
			//f->close();
		}
	}
}



void Superposer::unpack_files(std::function<void(std::string)> failure,
			      std::function<void()> success) {
	for (auto f: fsw) {
	        struct KeyHeader header;
		std::vector<cv::Rect> levers;
		std::vector<cv::Point> bitting;

		// Header
	       	f->read((char*)&header, sizeof(struct KeyHeader));
		if (header.MAGIC != 0xde57de57) {
			throw std::runtime_error("File is corruputed.");
		}

		// Levers
		for (size_t i = 0; i < 3; i++) {
			struct KeyLever l;

			f->read((char*)&l, sizeof(struct KeyLever));
			levers.push_back(cv::Rect(l.x, l.y, l.width, l.height));
		}

		// Key Body
		struct KeyBody entry;
		while (f->read((char*)&entry, sizeof(struct KeyBody))) {
			bitting.push_back(cv::Point(entry.x, entry.y));
		}

		struct Key k = {
			.header = header,
			.levers = levers,
			.bitting = bitting
		};
		keys.push_back(k);
	}
	return ;
}

static void raise_exception(std::string what) {
	throw std::runtime_error(what);
}

void Superposer::compute(int flow) {
	static constexpr void (Superposer::*flow_func[])
		(std::function<void(std::string)>,
		 std::function<void()>) = {
		&Superposer::unpack_files,
	};
	static constexpr int n_func =
		sizeof(flow_func) / sizeof(*flow_func);

	if (flow < n_func) {
		return (this->*flow_func[flow])(raise_exception, [=]() {
			return (this->compute(flow + 1));
		});
	}
}
