//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

//
// Define a bitting that is mainly used
// in association of difference from the
// blank key.
//

module compute_bitting(pos, deep, offset) {
    translate ([deep, pos, -2]) {
        scale ([7, offset, 1])
            cube (5);
    }
    translate ([-deep, pos, -2]) {
        scale ([-7, offset, 1])
            cube (5);
    }
}
