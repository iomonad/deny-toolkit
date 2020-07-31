//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

#include "Commons.hpp"

namespace Implicits {

    // WRITER
    std::ostream& operator<<(std::ostream &os, const KeyHeader &key) {
	os << key.MAGIC;
	return os;
    }

    // READER
    std::istream& operator>>(std::istream &is, KeyHeader &key) {
	is >> key.MAGIC;
	return is;
    }

}
