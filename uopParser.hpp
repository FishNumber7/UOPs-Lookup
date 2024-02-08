#ifndef UOPPARSER_HPP
#define UOPPARSER_HPP

#include <stdint.h>

const char* lookup(const char* instruction, const char* op1_size, const char* op2_size, const char* op3_size, const char* architecture);

#endif