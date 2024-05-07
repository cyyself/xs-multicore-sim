#include "verilated.h"
#ifdef VM_TRACE_FST
#include "verilated_fst_c.h"
#endif
#include "VXSTop.h"
#include "VXSTile.h"
#include "module_XSTile_io.h"
#include "axi4_ctrl.hpp"
#include "mmio_mem.hpp"
#include "uartlite.hpp"
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
    module_XSTile_io *tileIO_to_top[XS_NR_INST];
    for (int tile_idx=0; tile_idx<XS_NR_INST; tile_idx++) {
        tile[tile_idx] = new VXSTile;
        tileIO[tile_idx] = new module_XSTile_io(tile[tile_idx]);
        tileIO_to_top[tile_idx] = new module_XSTile_io;
        tile[tile_idx]->reset = 1;
        tile[tile_idx]->io_hartId = tile_idx;
    }
    connect_XSTile_to_top(tileIO_to_top, top);
#ifdef VM_TRACE_FST
    VerilatedFstC fst_top;
    VerilatedFstC fst_tile[XS_NR_INST];
    // connect fst for trace
    top->trace(&fst_top,0);
    fst_top.open("top.fst");
    for (int tile_idx=0; tile_idx<XS_NR_INST; tile_idx++) {
        tile[tile_idx]->trace(&fst_tile[tile_idx],0);
        fst_tile[tile_idx].open(std::string("tile_" + std::to_string(tile_idx) + ".fst").c_str());
    }
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
    memory_0_ctrl.add_dev(0x80000000, 0x80000000, &mem);
    axi4_ctrl peripheral_0_ctrl;
    uartlite uart;
    peripheral_0_ctrl.add_dev(0x40600000, 16, &uart);

    top->io_clock = 0;
    top->io_reset = 1;
    top->io_riscv_rst_vec_0 = 0x80000000;
    top->io_riscv_rst_vec_1 = 0x80000000;
    for (int rst_clk=0; rst_clk<10; rst_clk++) {
        top->io_clock = !top->io_clock;
        top->eval();
        for (int tile_idx=0; tile_idx<XS_NR_INST; tile_idx++) {
            *tileIO[tile_idx]->clock = !*tileIO[tile_idx]->clock;
            tileIO[tile_idx]->poke_from(tileIO_to_top[tile_idx]);
            tile[tile_idx]->eval();
            tileIO[tile_idx]->peek_to(tileIO_to_top[tile_idx]);
            tile[tile_idx]->eval();
        }
#ifdef VM_TRACE_FST
        if (enable_wavedump) {
            fst_top.dump(rst_clk);
            for (int tile_idx=0; tile_idx<XS_NR_INST; tile_idx++) {
                fst_tile[tile_idx].dump(rst_clk);
            }
        }
#endif
    }
    top->io_reset = 0;

    uint64_t ticks = 0;
    long max_ticks = 100000;

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
            for (int tile_idx=0; tile_idx<XS_NR_INST; tile_idx++) {
                *(tileIO[tile_idx]->reset) = top->io_reset;
                *(tileIO[tile_idx]->clock) = top->io_clock;
                tileIO[tile_idx]->poke_from(tileIO_to_top[tile_idx]);
                tile[tile_idx]->eval();
                tileIO[tile_idx]->peek_to(tileIO_to_top[tile_idx]);
                tile[tile_idx]->eval();
            }
            while (uart.exist_tx()) {
                char c = uart.getc();
                printf("%c", c);
                fflush(stdout);
            }
        }
        else {
            for (int tile_idx=0; tile_idx<XS_NR_INST; tile_idx++) {
                *(tileIO[tile_idx]->reset) = top->io_reset;
                *(tileIO[tile_idx]->clock) = top->io_clock;
                tile[tile_idx]->eval();
            }
        }
#ifdef VM_TRACE_FST
        if (enable_wavedump) {
            fst_top.dump(ticks+10);
            for (int tile_idx=0; tile_idx<XS_NR_INST; tile_idx++) {
                fst_tile[tile_idx].dump(ticks+10);
            }
        }
#endif
        ticks ++;
    }

#ifdef VM_TRACE_FST
    if (enable_wavedump) {
        fst_top.close();
        for (int tile_idx=0; tile_idx<XS_NR_INST; tile_idx++) {
            fst_tile[tile_idx].close();
        }
    }
#endif
    top->final();
    for (int tile_idx=0; tile_idx<XS_NR_INST; tile_idx++) {
        tile[tile_idx]->final();
    }
    return 0;
}
