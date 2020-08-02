//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

include <base.scad>;

//
// Maybe find a smarter way to
// generate profile ...
//
module protected_profile () {
    difference () {
        circle(r = 3.6, $fn = 25);
        translate([-6, -6, 0]) {
            square (4.6);
        };
        translate([1.45, 1.45, 0]) {
            square (3);
        };
        translate([1.5, -4.35, 0]) {
            square (3);
        };
        translate([-4.35, 1.47, 0]) {
            square (3);
        };
    }
}

module protected_base () {
    base_handle();
    
    translate ([0, 80, 0]) {
        rotate ([90, 0, 0]) {
           linear_extrude(height = 140, center = true,
                          convexity = 10, twist = 0) {
                protected_profile ();
           }
        }
    }
}

protected_base();
