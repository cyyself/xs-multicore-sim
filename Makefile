XS_RTL_DIR := ../XiangShan/build/rtl
VERILATOR_ARGS := --cc --trace --trace-fst -Wno-fatal --CFLAGS "-Os" -j `nproc`
FIRTOOL_ARGS := --disable-annotation-unknown --split-verilog --dedup --annotation-file=hier-anno.json --export-module-hierarchy --lowering-options="emittedLineLength=30000"

obj_dir/VXSTop.a: partitioned/XSTop.sv
	verilator $(VERILATOR_ARGS) --build $< -Ipartitioned --top XSTop

partitioned/XSTop.sv: vsrc/XSTop.sv
	mkdir -p partitioned
	python3 partition.py
	cp vsrc/STD_CLKGT_func.v partitioned/

vsrc/XSTop.sv: $(XS_RTL_DIR)/XSTop.fir $(XS_RTL_DIR)/XSTop.v.conf 
	mkdir -p vsrc
	firtool $(XS_RTL_DIR)/XSTop.fir $(FIRTOOL_ARGS) -o=vsrc