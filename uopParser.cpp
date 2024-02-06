#include "pugixml.hpp"
#include "uopParser.hpp"
#include <iostream>
#include <cstring>

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

const char* lookup(const char* instruction, const char* architecture)
{
    if (result) {
        current_instruction = instruction;
        arch = architecture;
        const char *uops = doc.find_node(find_instruction).find_child(find_arch).first_child().find_attribute(find_uops).value();
        return uops;
    } else {
        return NULL;
    }
}