#include "hash.hpp"
#include <iostream>
#include <iomanip>

int main()
{
    std::array<uint32_t, state_wcount> result = hash_block("hi");

    for (uint32_t w : result) {
        std::cout << std::hex << std::setfill('0') << std::setw(8) << w;
    }
    std::cout << "\n";

    std::array<uint32_t, state_wcount> result2 = hash_block("hi!");
    for (uint32_t w : result2) {
        std::cout << std::hex << std::setfill('0') << std::setw(8) << w;
    }
	return 0;
}