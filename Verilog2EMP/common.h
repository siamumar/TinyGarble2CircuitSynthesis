#ifndef UTIL_COMMON_H_
#define UTIL_COMMON_H_

#include <string>
#include <iostream>

using std::string;
using std::cerr;
using std::cout;
using std::endl;


#define SUCCESS 0
#define FAILURE (-1)

#define ROW_REDUCTION
#define FREE_XOR
#define DKC2

#define CONST_ZERO ((int64_t)-2)
#define CONST_ONE  ((int64_t)-1)
#define NUM_CONST 2

#define ANDGATE 8
#define ANDNGATE 4
#define NANDGATE 7
#define NANDNGATE 11
#define ORGATE 14
#define ORNGATE 13
#define NORGATE 1
#define NORNGATE 2
#define XORGATE 6
#define XNORGATE 9
#define NOTGATE 12
#define DFFGATE (-1)

// blocks
#define MUXGATE 15
#define HADDERGATE 16
#define FADDERGATE 17
#define INVALGATE 18

#define RDTSC ({unsigned long long res; \
  unsigned hi, lo;   \
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi)); \
  res =  ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 ); \
  res;})
#define fbits(v, p) ((v & (1 << p))>>p)

extern string dump_prefix;

#endif /* UTIL_COMMON_H_ */
