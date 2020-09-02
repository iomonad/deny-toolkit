//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

include <base.scad>;

module regular_base () {
    base_handle();
    
    translate ([0, 53, 0]) {
        rotate ([90, 0, 0]) {
           linear_extrude(height = 80, center = true,
                          convexity = 10, twist = 0) {
                circle(r = 3.6, $fn = 25);       
           }
        }
    }
}

regular_base();