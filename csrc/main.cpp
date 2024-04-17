#include "verilated.h"
#include "VXSTop.h"
#include "VXSTile.h"
#include "module_XSTile_io.h"

int main(int argc, char** argv, char** env) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    VXSTop* top = new VXSTop;
    VXSTile* tile[NR_TILES];
    module_XSTile_io *tileIO[NR_TILES];
    module_XSTile_io *tileIO_to_top[NR_TILES];

    for(int i = 0; i < NR_TILES; i++) {
        tile[i] = new VXSTile;
        tileIO[i] = new module_XSTile_io;
        connect_XSTile_to_top(tileIO_to_top, top);
    }
    
    top->io_clock = 0;
    top->io_reset = 0;

    long ticks = 100000;

    while(ticks--) {
        top->io_clock = !top->io_clock;
        top->eval();
    }

    return 0;
}
