#include "emp_circuit.h"

#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <new>
#include "log.h"

int WriteCircuit(const ReadCircuit& read_circuit, const string &file_name) {
	std::ofstream f(file_name.c_str(), std::ios::out);
	if (!f.is_open()) {
		LOG(ERROR) << "can't open " << file_name << endl;
		return -1;
	}
	
	/*In IdAssignment, constants 0 and 1 are assigned IDs -2 and -1 respecetively.
	Here we adjust the wire IDs such that constants 0 and 1 are assigned IDs 0 and 1 respecetively,
	and the rest of the wire IDs are shifted by 2. 
	num_wire includes the number of constant wires (2).
	*/
	
	int num_gate, num_wire, n0, n0_0, n1, n1_0, n2, n2_0, n3;
  
	num_gate = read_circuit.dff_size + read_circuit.gate_size;
	n0 = read_circuit.s_init_size + read_circuit.s_input_size;
	n0_0 = read_circuit.s_init_size;
	n1 = read_circuit.e_init_size + read_circuit.e_input_size;
	n1_0 = read_circuit.e_init_size;
	n2 = read_circuit.g_init_size + read_circuit.g_input_size;
	n2_0 = read_circuit.g_init_size;
	num_wire = num_gate + n0 + n1 + n2 + NUM_CONST;
	n3 = read_circuit.output_size;
	
	f << num_gate << " " << num_wire << endl;
	f << n0 << " " << n0_0 << " " << n1 << " " << n1_0 << " " << n2 << " " << n2_0 << " " <<  n3 << endl << endl;
	
	for (uint64_t i = 0; i < read_circuit.dff_size; i++) {
		f << "2 1 ";
		f << read_circuit.dff_list[i].input[0] + NUM_CONST << " " << read_circuit.dff_list[i].input[1] + NUM_CONST << " " << read_circuit.dff_list[i].output + NUM_CONST;	//0->D; 1->I
		f << " DFF" << endl;
	}
  
    for (uint64_t j = 0; j < read_circuit.gate_size; j++) {
		uint64_t i =  read_circuit.wire_mapping[read_circuit.task_schedule[j]];
		if(read_circuit.gate_list[i].type == NOTGATE) {
			f << "1 1 ";
			f << read_circuit.gate_list[i].input[0] + NUM_CONST << " " << read_circuit.gate_list[i].output + NUM_CONST;
		}
		else {
			f << "2 1 ";
			f << read_circuit.gate_list[i].input[0] + NUM_CONST << " " << read_circuit.gate_list[i].input[1] + NUM_CONST << " " << read_circuit.gate_list[i].output + NUM_CONST;
		}
		if(read_circuit.gate_list[i].type == NOTGATE) f << " INV";
		else if (read_circuit.gate_list[i].type == ANDGATE) f << " AND";
		else if (read_circuit.gate_list[i].type == XORGATE) f << " XOR";
		else{ 
			LOG(ERROR) << "unsupported gate." << endl;
			return FAILURE;
		}
		f << endl;
	}
  
  f.close();

  return 0;
}
