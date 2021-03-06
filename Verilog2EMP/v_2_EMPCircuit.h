#ifndef V_2_EMPCircuit_H_
#define V_2_EMPCircuit_H_

#include <string>
#include <vector>
#include <utility>
using std::vector;
using std::pair;
using std::string;

class ReadGateString {
 public:
  string input[2];
  string output;
  short type;
};

class ReadCircuitString {

 public:
  vector<ReadGateString> gate_list_string;
  vector<ReadGateString> dff_list_string;
  vector<pair<string, string>> assignment_list_string;
  uint64_t p_init_size;
  uint64_t g_init_size;
  uint64_t e_init_size;
  uint64_t s_init_size;
  uint64_t p_input_size;
  uint64_t g_input_size;
  uint64_t e_input_size;
  uint64_t s_input_size;
  uint64_t output_size;
  bool     has_terminate; // has terminate signal

  ReadCircuitString()
      : gate_list_string(0),
        dff_list_string(0) {
    p_init_size = 0;
    g_init_size = 0;
    e_init_size = 0;
    s_init_size = 0;
    p_input_size = 0;
    g_input_size = 0;
    e_input_size = 0;
    s_input_size = 0;
    output_size = 0;
    has_terminate = false;
  }
};

class ReadGate {
 public:
  int64_t input[2];
  int64_t output;
  short type;
};

class ReadCircuit {

 public:
  vector<uint64_t> output_list;
  vector<ReadGate> gate_list;
  vector<uint64_t> wire_mapping;
  vector<ReadGate> dff_list;
  vector<uint64_t> task_schedule;

  uint64_t p_init_size;
  uint64_t g_init_size;
  uint64_t e_init_size;
  uint64_t s_init_size;
  uint64_t p_input_size;
  uint64_t g_input_size;
  uint64_t e_input_size;
  uint64_t s_input_size;
  uint64_t dff_size;
  uint64_t gate_size;
  uint64_t output_size;
  uint64_t terminate_id; // terminate signal id, 0 in case of no signal

  uint64_t get_init_input_size() const {
    return p_init_size + g_init_size + e_init_size + s_init_size + p_input_size + g_input_size
        + e_input_size + s_input_size;
  }

  ReadCircuit()
      : output_list(0),
        gate_list(0),
        wire_mapping(0),
        dff_list(0),
        task_schedule(0) {
    p_init_size = 0;
    g_init_size = 0;
    e_init_size = 0;
    s_init_size = 0;
    p_input_size = 0;
    g_input_size = 0;
    e_input_size = 0;
    s_input_size = 0;
    dff_size = 0;
    gate_size = 0;
    output_size = 0;
    terminate_id = 0;
  }
};

int Verilog2EMPCircuit(const string &in_file_name, const string& out_mapping_filename,
                const string &out_file_name);

#endif
