//1 eksperimentas: visu reikalingu ivesciu generavimas
//sujungia: filegen.cpp, filemanip.cpp, structured_filegen.cpp
//srand(seed) kvieciamas pradzioje programos veikimo, galite atkurti visus failus
//del std::filesystem reikia naudoti C++17 ar velesni

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdint>
#include <filesystem>

const int seed = 53;
const std::string output_dir = "inputs/";

std::string out_path(const std::string& filename) {
	return output_dir + filename;
}

//help functions
std::string textgen(size_t len) {
	std::string text;
	text.reserve(len);
	for (size_t i = 0; i < len; ++i) {
		int c = 33 + (rand() % (126 - 33 + 1));
		text += static_cast<char>(c);
	}
	return text;
}

void write_file(const std::string& filename, const std::string& text) {
	std::ofstream f(filename, std::ios::binary); // tik baitai
	f << text;
	f.close();
	std::cout << "sukurtas failas pav. " << filename << "\n";
}

//change byte
uint8_t new_byte(uint8_t old_byte) {
	uint8_t byte;
	do {
		byte = static_cast<uint8_t>(33 + (rand() % (126 - 33 + 1)));
	} while (byte == old_byte);
	return byte;
}

size_t get_file_size(const std::string& path) {
	return std::filesystem::file_size(path);
}

//nuskaito filename, pakeicia 1 baita [index], issaugo i newfilename
void textchange(const std::string& filename, const std::string& newfilename, size_t index) {
	std::ifstream fin(filename, std::ios::binary);
	std::vector<uint8_t> data((std::istreambuf_iterator<char>(fin)),
		std::istreambuf_iterator<char>());
	fin.close();

	data[index] = new_byte(data[index]);

	std::ofstream fout(newfilename, std::ios::binary);
	fout.write(reinterpret_cast<const char*>(data.data()), data.size());
	fout.close();
}

size_t utf8_char_count(const std::string& s) {
	size_t count = 0;
	for (unsigned char c : s) {
		// jei high 2 bitai yra 10, jie nera pradzia char, jei jie yra 00, jie ascii, o jei 11 - pradzia char
		if ((c & 0b11000000) != 0b10000000) {
			++count;
		}
	}
	return count;
}

void run_experiment1() {
	srand(seed);

	std::filesystem::create_directories(output_dir);

	std::cout << "1 eksperimentas: ivesciu generavimas\n\n";
	write_file(out_path("empty.txt"), "");
	write_file(out_path("single_a.txt"), "a");
	write_file(out_path("single_b.txt"), "b");
	for (int i = 0; i < 9; ++i) {
		write_file(out_path("long" + std::to_string(i) + ".txt"), textgen(1200));
	}
	for (int i = 0; i < 3; ++i) {
		textchange(out_path("long" + std::to_string(i) + ".txt"), out_path("long" + std::to_string(i) + "_start.txt"), 0);
	}
	for (int i = 3; i < 6; ++i) {
		std::string filename = out_path("long" + std::to_string(i) + ".txt");
		size_t size = get_file_size(filename);
		textchange(filename, out_path("long" + std::to_string(i) + "_mid.txt"), size / 2);
	}
	for (int i = 6; i < 9; ++i) {
		std::string filename = out_path("long" + std::to_string(i) + ".txt");
		size_t size = get_file_size(filename);
		textchange(filename, out_path("long" + std::to_string(i) + "_end.txt"), size - 1);
	}
	write_file(out_path("struct_repeated.txt"), "aaaaaaaaaaaaaaaaaaaa");
	write_file(out_path("struct_order_original.txt"), "abcdefghij");
	write_file(out_path("struct_order_reorder.txt"), "jihgfedcba");
	write_file(out_path("struct_space_leading.txt"), " testinis tekstas");
	write_file(out_path("struct_space_trailing.txt"), "testinis tekstas ");
	write_file(out_path("struct_newline_no.txt"), "bababddodooowadiasid");
	write_file(out_path("struct_newline_yes.txt"), "bababddodooowadiasid\n");
	std::string utf8_text = "ąšėūčįąčšėųįšąčšųęšįųąčęų";
	write_file(out_path("utf8_case.txt"), utf8_text);
	size_t byte_count = utf8_text.size();
	size_t char_count = utf8_char_count(utf8_text);
	std::cout << "baitu skaicius: " << byte_count << "\n";
	std::cout << "simboliu skaicius: " << char_count << "\n";
	std::cout << "\nvisos ivestys sudarytos\n";
}