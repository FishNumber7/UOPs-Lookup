#include "pugixml.hpp"
#include <iostream>

class UOP_Lookup{

public:

    void set_architecture(std::string architecture) 
    {
        arch = architecture; 
    }

    int lookup(std::string instruction)
    {
        if (result) {
            this.instruction = instruction;
            return doc.find_child(find_instruction).find_child(find_arch).first_child().find_attribute(find_uops).value();
        }
    }


private:

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("instructions.xml");
    std::string arch;
    std:string instruction  = "";

    bool find_instruction(pugi::xml_node node) 
    {
        return strcmp(node.attribute("string"), instruction) == 0;
    }

    bool find_arch(pugi::xml_node node)
    {
        return strcmp(node.attribute("name"), arch) == 0;
    }

    bool find_uops(pugi::xml_attribute attr)
    {
        return strcmp(attr.name(), "uops") == 0;
    }

};