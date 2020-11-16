yosys -import

#for {set N 1} {$N < 4} {incr N} {

foreach N [list 8 16 32 64] {
	read_verilog -defer ../../SynthesisLibrary/syn_lib/*.v 
	read_verilog -defer -sv  sqrt.sv
	hierarchy -check -top sqrt -chparam N $N 
	procs; opt; flatten; opt; 
	techmap; opt;
	dfflibmap -liberty ../../SynthesisLibrary/lib_EMP/asic_cell_yosys.lib
	abc -liberty ../../SynthesisLibrary/lib_EMP/asic_cell_yosys.lib -script ../../SynthesisLibrary/lib_EMP/script.abc; 
	opt; clean; opt;
	opt_clean -purge
	stat -liberty ../../SynthesisLibrary/lib_EMP/asic_cell_yosys_area.lib
	write_verilog -noattr -noexpr -nohex syn/sqrt_${N}bit.v
}