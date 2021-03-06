#include "v_2_EMPCircuit.h"

#include "parse_netlist.h"
#include "scheduling.h"
#include "emp_circuit.h"
#include "log.h"

using std::endl;

int Verilog2EMPCircuit(const string &in_file_name, const string& out_mapping_filename,
                const string &out_file_name) {

  ReadCircuitString read_circuit_string;
  ReadCircuit read_circuit;

  if (ParseNetlist(in_file_name, &read_circuit_string) == FAILURE) {
    LOG(ERROR) << "parsing verilog netlist failed." << endl;
    return FAILURE;
  }
  if (IdAssignment(read_circuit_string, &read_circuit) == FAILURE) {
    LOG(ERROR) << "id assignment to netlist components failed." << endl;
    return FAILURE;
  }
  
  if (SortNetlist(&read_circuit, read_circuit_string) == FAILURE) {
    LOG(ERROR) << "topological sort failed." << endl;
    return FAILURE;
  }

  if (WriteMapping(read_circuit_string, read_circuit,
                   out_mapping_filename) == FAILURE) {
    LOG(ERROR) << "Write mapping failed." << endl;
    return FAILURE;
  }

  if (WriteCircuit(read_circuit, out_file_name) == FAILURE) {
    LOG(ERROR) << "write result to circuit file failed." << endl;
    return FAILURE;
  }

  return SUCCESS;
}

