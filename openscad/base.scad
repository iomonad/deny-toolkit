//
// (c) 2020 iomonad - <iomonad@riseup.net>
// See: https://github.com/iomonad/deny-toolkit
//

module base_handle () {
    
    module main () {
        scale([2,1,10])
        difference () {
            circle(d=30);
            circle(d=16);
        }
        // Renforcement Sphere
        translate([0,14,0]) {
             scale([1.5,1.2,1])
             sphere(r=5.09);
        }
    }
    
    main();
}