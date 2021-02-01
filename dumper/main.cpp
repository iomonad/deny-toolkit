//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "../Commons.hpp"

//
// WARNING: HORRIBLE PIECE OF CODE JUST
//          UNDER THIS COMMENT. THIS WAS MADE
//          FOR QUICK DEVELOPEMENT PURPOSES.
//          THANK FOR YOUR TOLERANT READING.
//

int main(int argc, char *argv[])
{
    std::ifstream input;

    if (argc != 2) {
	std::cout << "Usage: " << argv[0]
		  << " <file.kd>" << std::endl;
	exit(EXIT_FAILURE);
    }
    input.open(argv[1]);
    if (!input.good()) {
	input.close();
	throw std::runtime_error("File is incorrect.");
    } else {
	struct KeyHeader header;
	struct KeyBody entry;
	std::vector<cv::Point> bitting;

	input.read((char*)&header, sizeof(struct KeyHeader));

	std::cout << "[i] Loading file:" << argv[1] << std::endl;

	if (header.MAGIC != 0xde57de57) {
	    std::cerr << "Corruputed file, Exiting." << std::endl;
	    exit(EXIT_FAILURE);
	}

	std::cout << "[1] Combinaison name: " << header.name << std::endl;
	std::cout << "[2] Protected key: ";
	switch (header.protected_type) {
	case (0x00):
	    std::cout << "true" << std::endl;
	    break;
	default:
	    std::cout << "false" << std::endl;
	    break;
	}
	std::cout << "[3] Combinaison type: ";
	switch (header.combinaison_type) {
	case (0x00):
	    std::cout << "1" << std::endl;
	    break;
	case (0x01):
	    std::cout << "2" << std::endl;
	    break;
	case (0x02):
	    std::cout << "3" << std::endl;
	    break;
	default:
	    std::cout << "Exotic" << std::endl;
	    break;
	}

        // Levers dump
	std::cout << std::endl << "----- BEGIN LEVERS CODE -----"
		  << std::endl << std::endl;

	// Ho shit, very horrible piece of code rigth there.
	// Maybe declare a list of struct then map it to iostream
	// reader to collect results idiomaticaly ?
	KeyLever one, two, three;
	input.read((char*)&one, sizeof(struct KeyLever));
	input.read((char*)&two, sizeof(struct KeyLever));
	input.read((char*)&three, sizeof(struct KeyLever));
	std::vector<cv::Rect> levers {
		cv::Rect(one.x, one.y, one.width, one.height),
		cv::Rect(two.x, two.y, two.width, two.height),
		cv::Rect(three.x, three.y, three.width, three.height)
	};
	for (size_t i = 0; i < 3 ; i++) {
		cv::Rect node = levers.at(i);

		std::cout << "Levers " << i << ": "
			  << node << std::endl;
	}
	std::cout << std::endl << "----- END LEVERS CODE -----"
		  << std::endl;

	while (input.read((char*)&entry, sizeof(struct KeyBody))) {
	    bitting.push_back(cv::Point(entry.x, entry.y));
	}

	std::cout << "[4] Bitting chunk size: " << bitting.size() << std::endl;
	std::cout << std::endl << "----- BEGIN BITTING CODE -----"
		  << std::endl << std::endl;
	for (auto &e : bitting) {
	    static int i = 1;
	    std::cout << e;
	    if (i % 3 == 0)
	    	std::cout << std::endl;
	    else
		std::cout << " ";
	    i++;
	}
	std::cout << std::endl << "-----  END BITTING CODE  -----" << std::endl;
    }
    input.close();
    return EXIT_SUCCESS;
}
