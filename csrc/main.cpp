#include "verilated.h"
#include "VXSTop.h"
#include "VXSTile.h"
#include "module_XSTile_io.h"

int main(int argc, char** argv, char** env) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    VXSTop* top = new VXSTop;
    VXSTile* tile[XS_NR_INST];
    module_XSTile_io *tileIO[XS_NR_INST];
    module_XSTile_io **tileIO_to_top = new module_XSTile_io*[XS_NR_INST];

    for(int i=0; i<XS_NR_INST; i++) {
        tile[i] = new VXSTile;
        tileIO[i] = new module_XSTile_io(tile[i]);
        tileIO_to_top[i] = new module_XSTile_io;
    }
    connect_XSTile_to_top(tileIO_to_top, top);
    
    top->io_clock = 0;
    top->io_reset = 0;

    long ticks = 10000;

    while(ticks--) {
        top->io_clock = !top->io_clock;
        top->eval();
        if (top->io_clock) {
            // posedge
            for (int i=0; i<XS_NR_INST; i++) {
                *(tileIO[i]->reset) = top->io_reset;
                *(tileIO[i]->clock) = top->io_clock;
                tileIO[i]->poke_from(tileIO_to_top[i]);
                tile[i]->eval();
                tileIO[i]->peek_to(tileIO_to_top[i]);
            }
        }
        else {
            for (int i=0; i<XS_NR_INST; i++) {
                *tileIO[i]->reset = top->io_reset;
                *tileIO[i]->clock = top->io_clock;
                tile[i]->eval();
            }
        }
    }

    return 0;
}
