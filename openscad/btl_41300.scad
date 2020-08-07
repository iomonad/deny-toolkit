//  
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

include <protected_blank_sample.scad>;

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

module bitting() {
    compute_bitting(95, 9, 0.4);
    compute_bitting(100, 17, 1);
    compute_bitting(103.3, 10, 1);
    compute_bitting(106, 18, 1);

    compute_bitting(110, 8, 0.5);
    compute_bitting(115, 15, 1.1);
    compute_bitting(117, 12, 0.5);
    compute_bitting(117, 18, 2);
    compute_bitting(125, 15, 1.1);
    compute_bitting(125.5, 8, 0.7);
    
    compute_bitting(124, 12, 0.7);
    
    compute_bitting(129, 18, 1);
    compute_bitting(132, 6, 0.4);
    compute_bitting(133, 11, 0.7);
}

module btl_41300 () {
    difference () {
        protected_blank_sample();
        bitting();
    }
}


btl_41300();