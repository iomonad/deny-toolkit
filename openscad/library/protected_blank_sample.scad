//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

include <protected_base.scad>;

module blank_bitting_profile() {
    rotate (90) {
        square ([2.7, 40]);
    }
}

module blank_bitting() {
    translate ([20, 117, -1.3]) {
        rotate ([90, 0, 0]) {
                   linear_extrude(height = 50, center = true,
                          convexity = 10, twist = 0) {
                blank_bitting_profile ();
           }
        }
    }
}

module protected_blank_sample() {
    protected_base ();
    blank_bitting();
}
