#ifndef SCHEDULING_H_
#define SCHEDULING_H_

#include "v_2_EMPCircuit.h"

int SortNetlist(ReadCircuit* read_circuit,
                const ReadCircuitString& read_circuit_string);
int WriteMapping(const ReadCircuitString& read_circuit_string,
                 const ReadCircuit &read_circuit,
                 const string& out_mapping_filename);

#endif /* SCHEDULING_H_ */
