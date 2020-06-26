#ifndef PARSE_NETLIST_H_
#define PARSE_NETLIST_H_

#include "v_2_EMPCircuit.h"
#include <map>

string Type2StrGate(short itype);
int ParseNetlist(const string &file_name,
                 ReadCircuitString* read_circuit_string);
bool isOutPort(string output);
void AddWireArray(std::map<string, int64_t>& wire_name_table, const string& name,
                  uint64_t size, int64_t *wire_index);
int IdAssignment(const ReadCircuitString& read_circuit_string,
                 ReadCircuit* read_circuit);
int TopologicalSort(const ReadCircuit &read_circuit,
                    vector<int64_t>* sorted_list,
                    const ReadCircuitString& read_circuit_string);

#endif /* PARSE_NETLIST_H_ */
