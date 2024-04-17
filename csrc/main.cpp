#include "verilated.h"
#include "verilated_vcd_c.h"
#include "VXSTop.h"

int main(int argc, char** argv, char** env) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);
    VXSTop* top = new VXSTop;
    
    top->io_clock = 0;
    top->io_reset = 0;

    long ticks = 100000;
    
    while(ticks--) {
        top->io_clock = !top->io_clock;
        top->eval();
    }
    return 0;
}
