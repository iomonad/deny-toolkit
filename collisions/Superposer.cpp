//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#include <list>
#include <fstream>
#include <iostream>

#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>

#include "Superposer.hpp"

// Basic constructor, load files into
// fstream.

Superposer::Superposer(std::vector<std::string> fpaths) {
	for (const auto path: fpaths) {
		std::ifstream *s = new std::ifstream;
		s->open(path);

		if (!s->good()) {
			s->close();
			for (const auto f: fsw)
				f->close();
			throw std::runtime_error(
				"File " + path + " don't exists.");
		}
		//
		// This break object lifecycle, take
		// care of ressource acquisition.
		//
		fsw.push_back(s);
		std::cout << "[OK]  Loaded " << path
			  << "." << std::endl;
	}

	// CV Setup
	mat = cv::Mat(cv::Size(500, 500),
		CV_8UC3, cv::Scalar(0, 0, 0));
	cv::namedWindow(SUPERP_WIN,
			cv::WINDOW_AUTOSIZE | cv::WINDOW_GUI_NORMAL);

}

Superposer::~Superposer() {
	for (auto f: fsw) {
		if (f->is_open()) {
			f->close();
		}
	}
}


//
// Unpack each ifstream ref into exploitable
// key struct.
//

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
	return success();
}

//
// Ensure keys share same props
//

void Superposer::ensure_assoc(std::function<void(std::string)> failure,
			      std::function<void()> success) {
	unsigned short comb_type = 0;

	for (const auto &k : keys) {
		if (!comb_type)
			continue;
		if (k.header.combinaison_type != comb_type) {
			throw std::runtime_error("All files should have same combinaison size");
		}
	}
	std::cout << "[OK]  Key correlation correct, generating collision" << std::endl;
	return success();
}

static void draw_bitting(cv::Mat mat, std::vector<cv::Point> bitting,
			cv::Scalar color) {
    for (std::size_t i = 0; i < bitting.size(); ++i) {
	if ((i + 1) != bitting.size()) {
		cv::line(mat, bitting[i], bitting[i+1], color);
	}
    }
}

static void draw_levers(cv::Mat mat, std::vector<cv::Rect> levers,
			cv::Scalar color) {
	cv::Scalar lc = cv::Scalar(150, color[1], color[3]);
	for (std::size_t i = 0; i < levers.size(); ++i) {
		cv::rectangle(mat, levers.at(i), lc, 1);
	}
}

//
// Display each combinaison with shared materializer and
// unificated genese
//

void Superposer::process_layered_display(std::function<void(std::string)> failure,
					 std::function<void()> success) {
	char k;

	// TODO: Find smarter way to handle colors
	std::vector<cv::Scalar> colors {
		cv::Scalar (47, 255, 173),
		cv::Scalar (0, 255, 255),
		cv::Scalar (255, 255, 0),
		cv::Scalar (60, 20, 220),
		cv::Scalar (203, 192, 255),
		// Maybe add more scheme ?
	};

	for (size_t i = 0; i < keys.size(); i++) {
		// cv::Scalar color =
		// 	cv::Scalar(0x0, 255 - (i * 2), 0x0);
		draw_bitting(mat, keys[i].bitting, colors[i]);
		draw_levers(mat, keys[i].levers, colors[i]);
	}
	for (;;) {
	    cv::imshow(SUPERP_WIN, mat);
	    k = cv::waitKey(100);
	    if (k == 0x20 || k == 'q')
		    break;
	}
	return success();
}

static void raise_exception(std::string what) {
	throw std::runtime_error(what);
}

void Superposer::compute(int flow) {
	static constexpr void (Superposer::*flow_func[])
		(std::function<void(std::string)>,
		 std::function<void()>) = {
		&Superposer::unpack_files,
		&Superposer::ensure_assoc,
		&Superposer::process_layered_display
	};
	static constexpr int n_func =
		sizeof(flow_func) / sizeof(*flow_func);

	if (flow < n_func) {
		return (this->*flow_func[flow])(raise_exception, [=]() {
			return (this->compute(flow + 1));
		});
	}
}
