//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

include <protected_blank_sample.scad>;

module bitting () {
    translate ([120, 0, 0]) {
        sphere([2, 3, 3]);
    }
}

module btl_41300 () {
    difference () {
        protected_blank_sample();
        bitting();
    }
}


btl_41300();