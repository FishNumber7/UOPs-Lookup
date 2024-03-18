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

void build_csv() {
    std::string convert("ADC (M8, 0)");
    convert.replace(convert.find(" ("), 2, "_");
}

int main() {
    std::cout << build_csv() << std::endl;
}