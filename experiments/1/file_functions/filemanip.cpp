#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <filesystem>

int seed = 53;

size_t get_file_size(const std::string& path) {
    return std::filesystem::file_size(path);
}

uint8_t new_byte(uint8_t old_byte) {
	uint8_t byte;
	do {
		byte = static_cast<uint8_t>(33 + (rand() % (126 - 33 + 1)));
	} while (byte == old_byte);
	return byte;
}

bool textchange(const std::string& filename, const std::string& newfilename, size_t index) {
	std::ifstream fin(filename, std::ios::binary);
	std::vector<uint8_t> data((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
	fin.close();

	data[index] = new_byte(data[index]);

	std::ofstream fout(newfilename, std::ios::binary);
	fout.write(reinterpret_cast<const char*>(data.data()), data.size());
	fout.close();

	return true;
}

int main() {
    srand(seed);

	for (int i = 3; i < 6; ++i) {
		std::string filename = "long" + std::to_string(i) + ".txt";
		std::string newfilename = "long" + std::to_string(i) + "_mid.txt";
        size_t size = get_file_size(filename);
        size_t mid = size / 2;
		textchange(filename, newfilename, mid);
	}

	return 0;
}