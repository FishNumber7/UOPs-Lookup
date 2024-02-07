#include "pugixml.hpp"
#include "uopParser.hpp"
#include <iostream>
#include <cstring>
#include <stdint.h>

pugi::xml_document doc;
pugi::xml_parse_result result = doc.load_file("instructions.xml");
const char *arch = "";
const char *current_instruction  = "";

bool find_instruction(pugi::xml_node node) 
{
    return strcmp(node.attribute("string").value(), current_instruction) == 0;
}

bool find_arch(pugi::xml_node node)
{
    return strcmp(node.attribute("name").value(), arch) == 0;
}

bool find_uops(pugi::xml_attribute attr)
{
    return strcmp(attr.name(), "uops") == 0;
}

const char* convert(const char* instruction, operand op1, operand op2, operand op3) 
{
    if (!op1.size) {
        return instruction;
    } else {
        std::string converter(instruction);
        int position3;
        int position2;

        if (op3.size) {
            converter.append((char)op3.size).append(op3.orientation);
            position3 = converter.find_last_of('_');
            converter.replace(position3, 1, ", ");
        }
        
        if (op2.sizes) {
            converter.insert(position3, (char)op2.size).insert(position3 + 1, op2.orientation);
            position2 = converter.find_last_of('_');
            converter.replace(position2, 1, ", ");
        } 
        
        converter.insert(position2, (char)op.size).insert(position2 + 1, op1.orientation);
        converter.replace(converter.rfind("_"), 1, " (");
        converter += ")";
        return converter.c_str();
    }
}

const char* lookup(const char* instruction, operand op1_size, operand op2_size, operand op3_size, const char* architecture)
{
    if (result) {
        const char *formatted_inst = convert(instruction, op1_size, op2_size, op3_size);
        current_instruction = formatted_inst;
        arch = architecture;
        const char *uops = doc.find_node(find_instruction).find_child(find_arch).first_child().find_attribute(find_uops).value();
        return uops;
    } else {
        return NULL;
    }
}

int main()
{
    operand op1;
    operand op2;
    operand op3;
    op1.size = 16;
    op2.size = 8;
    op2.orientation = "H";
    op3.size = 0;
    std::cout << convert("ADD_R_R", op1, op2, op3, "ZEN4") << std::endl;
}