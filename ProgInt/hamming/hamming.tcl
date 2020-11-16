yosys -import

foreach N [list 8 16 32 64] {
	read_verilog -overwrite -defer ../../SynthesisLibrary/syn_lib/*.v 
	read_verilog -overwrite -defer hamming.v
	hierarchy -check -top hamming -chparam N $N -chparam CC 1 
	procs; opt; flatten; opt; 
	techmap; opt;
	dfflibmap -liberty ../../SynthesisLibrary/lib_EMP/asic_cell_yosys.lib
	abc -liberty ../../SynthesisLibrary/lib_EMP/asic_cell_yosys.lib -script ../../SynthesisLibrary/lib_EMP/script.abc; 
	opt; clean; opt;
	opt_clean -purge
	stat -liberty ../../SynthesisLibrary/lib_EMP/asic_cell_yosys_area.lib
	write_verilog -noattr -noexpr -nohex syn/hamming_${N}bit_1cc.v
}


set COMMENTED_OUT {

	foreach N [list 1 2 4 8] {
		read_verilog -overwrite -defer ../../SynthesisLibrary/syn_lib/*.v 
		read_verilog -overwrite -defer hamming.v
		hierarchy -check -top hamming -chparam N $N -chparam CC $N 
		procs; opt; flatten; opt; 
		techmap; opt;
		dfflibmap -liberty ../../SynthesisLibrary/lib_EMP/asic_cell_yosys.lib
		abc -liberty ../../SynthesisLibrary/lib_EMP/asic_cell_yosys.lib -script ../../SynthesisLibrary/lib_EMP/script.abc; 
		opt; clean; opt;
		opt_clean -purge
		stat -liberty ../../SynthesisLibrary/lib_EMP/asic_cell_yosys_area.lib
		write_verilog -noattr -noexpr -nohex syn/hamming_${N}bit_${N}cc.v
}

}