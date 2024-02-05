#include "pugixml.hpp"
#include <iostream>

int[22] ignore_list = {'AMD_INVLPGB', 'AMX_BF16', 'AMX_INT8', 'AMX_TILE', 'AVX_IFMA', 'AVX_NE_CONVERT', 'AVX_VNNI', 'AVX_VNNI_INT8', 'CMPCCXADD', 'ENQCMD', 'HRESET', 'ICACHE_PREFETCH', 'KEYLOCKER', 'KEYLOCKER_WIDE', 'MSRLIST', 'RAO_INT', 'SERIALIZE', 'SNP', 'TDX', 'TSX_LDTRK', 'UINTR', 'WRMSRNS'};

int main()
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("instructions.xml");
    if (!result)
        return -1;

    for (pugi::xml_node tool: doc.children("instruction")) {
        if ({})
    }

}