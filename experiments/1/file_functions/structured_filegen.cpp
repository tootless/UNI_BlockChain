#include <fstream>
#include <string>
#include <iostream>

void write_file(const std::string& filename, const std::string& text) {
	std::ofstream f(filename, std::ios::binary);
	f << text;
	f.close();
}

size_t utf8_char_count(const std::string& s) {
	size_t count = 0;
	for (unsigned char c : s) {
		if ((c & 0b11000000) != 0b10000000) { //if top 2 bits are 10, its a continuation, if not, then its 11 or 0, so either first byte of character or a full character
			count++;
		}
	}
	return count;
}

int main() {
	// pasikartojantys simboliai
	write_file("struct_repeated.txt", "aaaaaaaaaaaaaaaaaaaa");

	// skirtinga simboliu tvarka
	write_file("struct_order_original.txt", "abcdefghij");
	write_file("struct_order_reorder.txt", "jihgfedcba");

	// tarpai start/end
	write_file("struct_space1.txt", " testinis tekstas");
	write_file("struct_space2.txt", "testinis tekstas ");

	// su ir be \n
	write_file("struct_newline_no.txt", "bababddodooowadiasid");
	write_file("struct_newline_yes.txt", "bababddodooowadiasid\n");

	// utf8 no ascii tekstas
	std::string utf8_text = "ąšėūčįąčšėųįšąčšųęšįųąčęų";

	std::string filename = "utf8_case.txt";
	write_file(filename, utf8_text);

	size_t byte_count = utf8_text.size();
	size_t char_count = utf8_char_count(utf8_text);

	std::cout << "utf8 failo info: \n";
	std::cout << "tekstas: " << utf8_text << "\n";
	std::cout << "baitu sk: " << byte_count << "\n";
	std::cout << "simboliu sk: " << char_count << "\n";
	std::cout << "(baitai - simboliai): " << (byte_count - char_count);

	return 0;
}