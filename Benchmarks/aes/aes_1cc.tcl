yosys -import

read_verilog ../../SynthesisLibrary/syn_lib/*.v

read_verilog -sv aes_1cc.sv  AddRoundKey.sv  KeyExpansionSeq.sv  KeyExpansion.sv  MixColumns.sv  ShiftRows.sv  SubBytes.sv
hierarchy -check -top aes_1cc
procs; opt; flatten; opt; 
techmap ; opt;
dfflibmap -liberty ../../SynthesisLibrary/lib_EMP/asic_cell_yosys.lib
abc -liberty ../../SynthesisLibrary/lib_EMP/asic_cell_yosys.lib -script ../../SynthesisLibrary/lib_EMP/script.abc; 
opt; clean; opt;
opt_clean -purge
stat -liberty ../../SynthesisLibrary/lib_EMP/asic_cell_yosys_area.lib
write_verilog -noattr -noexpr -nohex syn/aes_1cc_syn.v