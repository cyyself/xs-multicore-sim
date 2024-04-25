#include "verilated.h"
#ifdef VM_TRACE_FST
#include "verilated_fst_c.h"
#endif
#include "VXSTop.h"
#include "VXSTile.h"
#include "module_XSTile_io.h"
#include "axi4_ctrl.hpp"
#include "mmio_mem.hpp"
#ifdef VM_TRACE_FST
bool enable_wavedump = true;
#endif

void bind_wire(axi4_ptr_t &memory_0_port, axi4_ptr_t &peripheral_0_port, VXSTop* top) {
    // memory_0
    // aw
    memory_0_port.awid = reinterpret_cast<uint8_t*>(&(top->memory_0_aw_bits_id));
    memory_0_port.awaddr = reinterpret_cast<uint8_t*>(&(top->memory_0_aw_bits_addr));
    memory_0_port.awlen = reinterpret_cast<uint8_t*>(&(top->memory_0_aw_bits_len));
    memory_0_port.awsize = reinterpret_cast<uint8_t*>(&(top->memory_0_aw_bits_size));
    memory_0_port.awburst = reinterpret_cast<uint8_t*>(&(top->memory_0_aw_bits_burst));
    memory_0_port.awvalid = reinterpret_cast<uint8_t*>(&(top->memory_0_aw_valid));
    memory_0_port.awready = reinterpret_cast<uint8_t*>(&(top->memory_0_aw_ready));
    // w
    memory_0_port.wdata = reinterpret_cast<uint8_t*>(&(top->memory_0_w_bits_data));
    memory_0_port.wstrb = reinterpret_cast<uint8_t*>(&(top->memory_0_w_bits_strb));
    memory_0_port.wlast = reinterpret_cast<uint8_t*>(&(top->memory_0_w_bits_last));
    memory_0_port.wvalid = reinterpret_cast<uint8_t*>(&(top->memory_0_w_valid));
    memory_0_port.wready = reinterpret_cast<uint8_t*>(&(top->memory_0_w_ready));
    // b
    memory_0_port.bid = reinterpret_cast<uint8_t*>(&(top->memory_0_b_bits_id));
    memory_0_port.bresp = reinterpret_cast<uint8_t*>(&(top->memory_0_b_bits_resp));
    memory_0_port.bvalid = reinterpret_cast<uint8_t*>(&(top->memory_0_b_valid));
    memory_0_port.bready = reinterpret_cast<uint8_t*>(&(top->memory_0_b_ready));
    // ar
    memory_0_port.arid = reinterpret_cast<uint8_t*>(&(top->memory_0_ar_bits_id));
    memory_0_port.araddr = reinterpret_cast<uint8_t*>(&(top->memory_0_ar_bits_addr));
    memory_0_port.arlen = reinterpret_cast<uint8_t*>(&(top->memory_0_ar_bits_len));
    memory_0_port.arsize = reinterpret_cast<uint8_t*>(&(top->memory_0_ar_bits_size));
    memory_0_port.arburst = reinterpret_cast<uint8_t*>(&(top->memory_0_ar_bits_burst));
    memory_0_port.arvalid = reinterpret_cast<uint8_t*>(&(top->memory_0_ar_valid));
    memory_0_port.arready = reinterpret_cast<uint8_t*>(&(top->memory_0_ar_ready));
    // r
    memory_0_port.rid = reinterpret_cast<uint8_t*>(&(top->memory_0_r_bits_id));
    memory_0_port.rdata = reinterpret_cast<uint8_t*>(&(top->memory_0_r_bits_data));
    memory_0_port.rresp = reinterpret_cast<uint8_t*>(&(top->memory_0_r_bits_resp));
    memory_0_port.rlast = reinterpret_cast<uint8_t*>(&(top->memory_0_r_bits_last));
    memory_0_port.rvalid = reinterpret_cast<uint8_t*>(&(top->memory_0_r_valid));
    memory_0_port.rready = reinterpret_cast<uint8_t*>(&(top->memory_0_r_ready));
    // peripheral_0
    // aw
    peripheral_0_port.awid = reinterpret_cast<uint8_t*>(&(top->peripheral_0_aw_bits_id));
    peripheral_0_port.awaddr = reinterpret_cast<uint8_t*>(&(top->peripheral_0_aw_bits_addr));
    peripheral_0_port.awlen = reinterpret_cast<uint8_t*>(&(top->peripheral_0_aw_bits_len));
    peripheral_0_port.awsize = reinterpret_cast<uint8_t*>(&(top->peripheral_0_aw_bits_size));
    peripheral_0_port.awburst = reinterpret_cast<uint8_t*>(&(top->peripheral_0_aw_bits_burst));
    peripheral_0_port.awvalid = reinterpret_cast<uint8_t*>(&(top->peripheral_0_aw_valid));
    peripheral_0_port.awready = reinterpret_cast<uint8_t*>(&(top->peripheral_0_aw_ready));
    // w
    peripheral_0_port.wdata = reinterpret_cast<uint8_t*>(&(top->peripheral_0_w_bits_data));
    peripheral_0_port.wstrb = reinterpret_cast<uint8_t*>(&(top->peripheral_0_w_bits_strb));
    peripheral_0_port.wlast = reinterpret_cast<uint8_t*>(&(top->peripheral_0_w_bits_last));
    peripheral_0_port.wvalid = reinterpret_cast<uint8_t*>(&(top->peripheral_0_w_valid));
    peripheral_0_port.wready = reinterpret_cast<uint8_t*>(&(top->peripheral_0_w_ready));
    // b
    peripheral_0_port.bid = reinterpret_cast<uint8_t*>(&(top->peripheral_0_b_bits_id));
    peripheral_0_port.bresp = reinterpret_cast<uint8_t*>(&(top->peripheral_0_b_bits_resp));
    peripheral_0_port.bvalid = reinterpret_cast<uint8_t*>(&(top->peripheral_0_b_valid));
    peripheral_0_port.bready = reinterpret_cast<uint8_t*>(&(top->peripheral_0_b_ready));
    // ar
    peripheral_0_port.arid = reinterpret_cast<uint8_t*>(&(top->peripheral_0_ar_bits_id));
    peripheral_0_port.araddr = reinterpret_cast<uint8_t*>(&(top->peripheral_0_ar_bits_addr));
    peripheral_0_port.arlen = reinterpret_cast<uint8_t*>(&(top->peripheral_0_ar_bits_len));
    peripheral_0_port.arsize = reinterpret_cast<uint8_t*>(&(top->peripheral_0_ar_bits_size));
    peripheral_0_port.arburst = reinterpret_cast<uint8_t*>(&(top->peripheral_0_ar_bits_burst));
    peripheral_0_port.arvalid = reinterpret_cast<uint8_t*>(&(top->peripheral_0_ar_valid));
    peripheral_0_port.arready = reinterpret_cast<uint8_t*>(&(top->peripheral_0_ar_ready));
    // r
    peripheral_0_port.rid = reinterpret_cast<uint8_t*>(&(top->peripheral_0_r_bits_id));
    peripheral_0_port.rdata = reinterpret_cast<uint8_t*>(&(top->peripheral_0_r_bits_data));
    peripheral_0_port.rresp = reinterpret_cast<uint8_t*>(&(top->peripheral_0_r_bits_resp));
    peripheral_0_port.rlast = reinterpret_cast<uint8_t*>(&(top->peripheral_0_r_bits_last));
    peripheral_0_port.rvalid = reinterpret_cast<uint8_t*>(&(top->peripheral_0_r_valid));
    peripheral_0_port.rready = reinterpret_cast<uint8_t*>(&(top->peripheral_0_r_ready));
}

int main(int argc, char** argv, char** env) {
    Verilated::commandArgs(argc, argv);
#ifdef VM_TRACE_FST
    Verilated::traceEverOn(enable_wavedump);
#endif
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
#ifdef VM_TRACE_FST
    VerilatedFstC fst;
    // connect fst for trace
    top->trace(&fst,0);
    fst.open("trace.fst");
#endif
    // memory
    mmio_mem mem(0x80000000, "../simple-sw-workbench/start.bin");

    // connect peripherals and mem
    axi4_ptr_t memory_0_port(36, 256, 14, false);
    // 0x3800_0000 - 0x3fff_ffff
    axi4_ptr_t peripheral_0_port(31, 64, 2, false);
    bind_wire(memory_0_port, peripheral_0_port, top);

    axi4_ptr_t memory_0_port_buf(36, 256, 14);
    axi4_ptr_t peripheral_0_port_buf(31, 64, 2);

    axi4_ctrl memory_0_ctrl;
    memory_0_ctrl.add_dev(0x00000000, 0x80000000, &mem);
    axi4_ctrl peripheral_0_ctrl;
    
    top->io_clock = 0;
    top->io_reset = 0;
    top->io_riscv_rst_vec_0 = 0x80000000;
    top->io_riscv_rst_vec_1 = 0x80000000;

    uint64_t ticks = 0;
    long max_ticks = 1000;

    while(ticks < max_ticks) {
        top->io_clock = !top->io_clock;
        top->eval();
        if (top->io_clock) {
            // posedge
            memory_0_ctrl.tick(memory_0_port_buf);
            peripheral_0_ctrl.tick(peripheral_0_port_buf);
            memory_0_port_buf.update_output(memory_0_port);
            peripheral_0_port_buf.update_output(peripheral_0_port);
            memory_0_port_buf.update_input(memory_0_port);
            peripheral_0_port_buf.update_input(peripheral_0_port);
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
