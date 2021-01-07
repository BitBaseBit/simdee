#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "gtest/gtest.h"
#include "jsimd/config/jsimd_instruction_set.hpp"

using info_map_type = std::map<int, std::string>;

info_map_type init_instruction_map()
{
    info_map_type res;
    res[JSIMD_ARM7_NEON_VERSION] = "ARMv7 Neon";
    res[JSIMD_ARM8_32_NEON_VERSION] = "ARMv8 32bit Neon";
    res[JSIMD_ARM8_64_NEON_VERSION] = "ARMv8 64bit Neon";
    res[JSIMD_VERSION_NUMBER_NOT_AVAILABLE] = "No SIMD available";
    return res;
}

std::string get_instruction_set_name()
{
    static info_map_type info_map(init_instruction_map());
    return info_map[JSIMD_INSTR_SET];
}

int main(int argc, char* argv[])
{
    std::ofstream out("log/jsimd_info.log", std::ios_base::out);
    std::string instruction_set = get_instruction_set_name();
    out << "Instruction set: " << instruction_set << std::endl;
    std::cout << "Instruction set: " << instruction_set << std::endl;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
