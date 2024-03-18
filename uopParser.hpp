#ifndef UOPPARSER_HPP
#define UOPPARSER_HPP

const char* lookup(const char* instruction, const char* op1_size, const char* op2_size, const char* op3_size, const char* architecture);

const char* naive_lookup(const char* instruction, const char* architecture);

#endif