#include "verilated.h"
#ifdef VM_TRACE_FST
#include "verilated_fst_c.h"
#endif
#include "VXSTop.h"
#include "VXSTile.h"
#include "module_XSTile_io.h"

#ifdef VM_TRACE_FST
bool enable_wavedump = true;
#endif
int main(int argc, char** argv, char** env) {
    Verilated::commandArgs(argc, argv);
#ifdef VM_TRACE_FST
    Verilated::traceEverOn(enable_wavedump);
#endif
    VXSTop* top = new VXSTop;
    VXSTile* tile[XS_NR_INST];
    module_XSTile_io *tileIO[XS_NR_INST];
    module_XSTile_io **tileIO_to_top = new module_XSTile_io*[XS_NR_INST];
#ifdef VM_TRACE_FST
    VerilatedFstC fst;
    // connect fst for trace
    top->trace(&fst,0);
    fst.open("trace.fst");
#endif
    for(int i=0; i<XS_NR_INST; i++) {
        tile[i] = new VXSTile;
        tileIO[i] = new module_XSTile_io(tile[i]);
        tileIO_to_top[i] = new module_XSTile_io;
    }
    connect_XSTile_to_top(tileIO_to_top, top);
    
    top->io_clock = 0;
    top->io_reset = 0;
    top->io_riscv_rst_vec_0 = 0x80000000;
    top->io_riscv_rst_vec_1 = 0x80000000;

    uint64_t ticks = 0;
    long max_ticks = 10000;

    while(ticks < max_ticks) {
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
#ifdef VM_TRACE_FST
        if (enable_wavedump) {
            fst.dump(ticks);
        }
#endif
        ticks ++;
    }

#ifdef VM_TRACE_FST
    if (enable_wavedump) fst.close();
#endif
    top->final();
    return 0;
}
