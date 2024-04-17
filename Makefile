XS_RTL_DIR := ../XiangShan/build/rtl
PARTITION_MODULE := XSTile
NR_TILES := 2
VERILATOR_ARGS := --cc --trace-fst -Wno-fatal --CFLAGS "-Os -DNR_TILES=$(NR_TILES)" -j `nproc` --threads 8
FIRTOOL_ARGS := --disable-annotation-unknown --split-verilog --dedup --annotation-file=hier-anno.json --export-module-hierarchy --lowering-options="emittedLineLength=30000"

obj_dir/VXSTop: partitioned/XSTop.sv csrc/main.cpp obj_dir/libV$(PARTITION_MODULE).a obj_dir/module_XSTile_io.cpp
	verilator $(VERILATOR_ARGS) --build --exe $(realpath $^) -Ipartitioned --top XSTop

obj_dir/libV$(PARTITION_MODULE).a: partitioned/$(PARTITION_MODULE).sv
	cp $(XS_RTL_DIR)/Difftest* partitioned/
	verilator $(VERILATOR_ARGS) --build $^ -Ipartitioned --top $(PARTITION_MODULE)

partitioned/XSTop.sv: vsrc/XSTop.sv partition.py
	mkdir -p partitioned obj_dir
	python3 partition.py -t $(PARTITION_MODULE) -d obj_dir -m clock
	cp vsrc/STD_CLKGT_func.v partitioned/

vsrc/XSTop.sv: $(XS_RTL_DIR)/XSTop.fir $(XS_RTL_DIR)/XSTop.v.conf 
	mkdir -p vsrc
	firtool $(XS_RTL_DIR)/XSTop.fir $(FIRTOOL_ARGS) -o=vsrc