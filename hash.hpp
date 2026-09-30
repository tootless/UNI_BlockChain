#pragma once
#include <string>
#include <cstdint>
#include <iostream>
#include <array>

constexpr size_t state_wcount = 8; //32 bits per word, 256 bit output
constexpr std::array<uint32_t, state_wcount> state_words = { //phi / (prime starting from 3) * 2^32
    2316467687u, 1389880613u, 992771867u, 631763915u,
    534569467u, 408788415u, 365758057u, 302147959u
};
constexpr size_t block_size = 32;
constexpr uint32_t value = 2654435769u;   // 2^32/phi

void mix_block(std::array<uint32_t, state_wcount>& state, const std::string& block) {
    for (unsigned char c : block) {
        size_t i = 0;
        for (unsigned char c : block) {
            state[i % state_wcount] += c;
            state[i % state_wcount] *= value;
            ++i;
        }
    }
}

std::array<uint32_t, state_wcount> hash_block(const std::string& text) {
    std::array<uint32_t, state_wcount> state = state_words;

    for (size_t offset = 0; offset < text.size(); offset += block_size) {
        std::string block = text.substr(offset, block_size);
        mix_block(state, block);
    }

    return state;
}