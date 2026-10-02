#pragma once
#include <string>
#include <cstdint>
#include <iostream>
#include <array>
#include <vector>

//hashing based on golden ratio (phi)

constexpr size_t state_wcount = 8; //8 * 32 bits = 256
constexpr std::array<uint32_t, state_wcount> state_words = { //phi / (prime starting from 3) * 2^32
	2316467687u, 1389880613u, 992771867u, 631763915u,
	534569467u, 408788415u, 365758057u, 302147959u
};
constexpr size_t block_size = 32; //iteration input size
constexpr uint32_t value = 2654435769u; // 2^32/phi

//
void mix_block(std::array<uint32_t, state_wcount>& state, const std::vector<uint8_t>& block) {
	size_t i = 0;
	for (unsigned char c : block) {
		size_t firstw = i % state_wcount; // 0 3 1 4 2 5 3 6 4 7 5 8
		size_t secondw = (i + 3) % state_wcount;

		state[firstw] += c;
		state[firstw] *= value;

		state[secondw] ^= state[firstw]; // 
		++i;
	}
}

//uses the MD (merkel damgard) scheme
//begins with a 32 byte or smaller vector of input data (text),
//adds a length marker,
//adds zeros until 8 last bytes are left,
//
//returns 32 bytes of data, padded
std::vector <uint8_t> pad(const std::string& data) {
	uint64_t byte_len = static_cast<uint32_t>(data.size());
	std::vector<uint8_t> padded(data.begin(),data.end());
	padded.push_back(0b10000000); //length marker
	while (padded.size() % block_size != (block_size - 8)) {
		padded.push_back(0x00); //0b00000000
	}
	//rshift - 
	//and truncate - (11...u) gets trailing 0s to match length, then last 8bits are 1s
	for (int i = 0; i < 8; ++i) {
		padded.push_back(static_cast<uint8_t>((byte_len >> (8 * i)) & 0b11111111));
	}
	return padded;
}

// hashed result function
std::array<uint32_t, state_wcount> hash_block(const std::string& text) {
	std::array<uint32_t, state_wcount> state = state_words;
	std::vector<uint8_t> padded = pad(text);

	for (size_t offset = 0; offset < padded.size(); offset += block_size) {
		std::vector<uint8_t> block(padded.begin() + offset, padded.begin() + offset + block_size);
		mix_block(state, block);
	}

	return state;
}

void rotate() {

}