#include "pugixml.hpp"
#include "uopParser.hpp"
#include <iostream>
#include <cstring>
#include <stdint.h>
#include <string>

pugi::xml_document doc;
pugi::xml_parse_result result = doc.load_file("instructions.xml");
const char *arch = "";
std::string current_instruction  = "";

bool find_instruction(pugi::xml_node node) 
{
    return strcmp(node.attribute("string").value(), current_instruction.c_str()) == 0;
}

bool find_arch(pugi::xml_node node)
{
    return strcmp(node.attribute("name").value(), arch) == 0;
}

bool find_uops(pugi::xml_attribute attr)
{
    return strcmp(attr.name(), "uops") == 0;
}

std::string convert(const char* instruction, const char* op1_size, const char* op2_size, const char* op3_size) 
{
    if (!op1_size) {
        return instruction;
    } else {
        std::string converter(instruction);
        std::string converted_inst;
        size_t position3 = converter.size();
        size_t position2 = converter.size();
        converted_inst += ")";

        if (op3_size) {
            position3 = converter.find_last_of('_');
            converted_inst.insert(0, op3_size).insert(0, 1, converter[position3 + 1]).insert(0, ", ");
        }

        if (op2_size) {
            position2 = converter.find_last_of('_', position3 - 1);
            converted_inst.insert(0, op2_size).insert(0, 1, converter[position2 + 1]).insert(0, ", ");
        } 

        size_t position1 = converter.find_last_of('_', position2 - 1);
        converted_inst.insert(0, op1_size).insert(0, 1, converter[position1 + 1]).insert(0, " (").insert(0, converter.substr(0, position1));
        
        return converted_inst;
    }
}

std::string naive_convert(const char* instruction)
{
    std::string converter(instruction);
    int op_count = 0;
    int position = converter.find_first_of('_');
    while (position != -1) {
        int last_position = position;
        position = converter.find_first_of('_', last_position + 1);
        if (last_position != -1 && (position - last_position == 2 || converter.size() - last_position == 2)) {
            op_count++;
        }
    }

    switch(op_count) {
        case 0: 
            return convert(instruction, NULL, NULL, NULL);
            break;
        case 1:
            return convert(instruction, "64", NULL, NULL);
            break;
        case 2:
            return convert(instruction, "64", "32", NULL);
            break;
        case 3:
            return convert(instruction, "64", "32", "32");
            break;
        default:
            return "not found";
            break;
    }
}

const char* lookup(const char* instruction, const char* op1_size, const char* op2_size, const char* op3_size, const char* architecture)
{
    if (result) {
        current_instruction = convert(instruction, op1_size, op2_size, op3_size);
        arch = architecture;
        return doc.find_node(find_instruction).find_child(find_arch).first_child().find_attribute(find_uops).value();
    } else {
        return NULL;
    }
}

const char* naive_lookup(const char* instruction, const char* architecture)
{
     if (result) {
        current_instruction = naive_convert(instruction);
        arch = architecture;
        return doc.find_node(find_instruction).find_child(find_arch).first_child().find_attribute(find_uops).value();
    } else {
        return NULL;
    }
}