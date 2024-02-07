#ifndef UOPPARSER_HPP
#define UOPPARSER_HPP

#include <stdint.h>

struct operand {
    uint8_t size;
    const char[1] orientation = "";
}

const char* lookup(const char* instruction, operand op1_size, operand op2_size, operand op3_size, const char* architecture);

#endif