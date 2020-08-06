//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

include <protected_blank_sample.scad>;

module mkbit(l, x, y, z) {
    translate([x, l, -2]) {
        scale([y, z, 1.5])
            cube(5);
    }
    translate([-x, l, -2]) {
        scale([-y, z, 1.5])
            cube(5);
    } 
}

module bitting () {    
    mkbit(100, 10, 2.1, 1.1);
    mkbit(110, 15, 1.4, 0.9);
    mkbit(118, 5, 4.5, 0.7);
    mkbit(120, 14, 4.4, 1.5);
    mkbit(130, 10, 4.2, 0.4);
    mkbit(135, 5, 4.2, 0.4);

}

module btl_41300 () {
    difference () {
        protected_blank_sample();
        bitting();
    }
}


btl_41300();