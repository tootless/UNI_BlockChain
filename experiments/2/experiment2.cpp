//2 eksperimentas: hex formato validavimas bei rankines/failo ivesties tarpusavio patikrinimas
//

#include "experiment2.hpp"
#include "hash.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>

const size_t expected_hex_len = 256/4; //256bit hash

bool check_hex(const std::string& hex, const size_t len) {

	if (hex.size() != len) {
		std::cout << "KLAIDA: ilgis: " << hex.size() << "\nreikia, kad ilgis butu: " << len << "\n";
		return false;
	}

	for (char c : hex) {
		bool is_valid_hex = (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f');
		if (!is_valid_hex) {
			std::cout << "KLAIDA: netinkamas simbolis, " << c << "nera mazoji hex raide/skaitmuo\n";
			return false;
		}
	}

	return true;
}

//pilna patikra
void check_case(const std::string& label, const std::string& filename) {
	auto data = read_data(filename);
	auto result = hash_block(data);
	std::string hex = to_hex(result);

	std::cout << label << "\n";
	std::cout << "deklaruotas ilgis: " << expected_hex_len * 4 << " bitu, t.y " << expected_hex_len << " hex simboliu\n";
	std::cout << "hash: " << hex << "\n";

	if (check_hex(hex, expected_hex_len)) {
		std::cout << "ilgis ir formatas teisingi, yra " << expected_hex_len << " hex simboliu\n";
	}
	std::cout << "\n";
}

void manual_vs_file(std::string& manual_input,std::string& filename) {
	auto manual_result = hash_block(manual_input);
	std::string manual_hex = to_hex(manual_result);

	write_data(filename,manual_input);

	std::vector<uint8_t> file_data = read_data(filename);

	auto file_result = hash_block(file_data);
	std::string file_hex = to_hex(file_result);

	std::cout << "rankinio teksto hash: " << manual_hex << "\n";
	std::cout << "failo hash:    " << file_hex << "\n";

	if (manual_hex == file_hex) {
		std::cout << "rezultatai sutampa, ivesties baitai vienodi\n";
	}
	else {
		std::cout << "rezultatai skiriasi, nors baitai vienodi\n";
	}
	std::cout << "\n";
}

void run_experiment2() {
	std::cout << "2 eksperimentas: isvesties formatavimo/teisingumo patikra\n\n";

	std::cout << "hex bei maisos ilgio patikra:\n\n";

	check_case("tuscia ivestis:", "empty.txt");
	check_case("1 baitas, #1:", "single_a.txt");
	check_case("1 baitas, #2:", "single_b.txt");

	std::cout << "\natsitiktinio ascii turinio failai, >1000 baitu:\n\n";
	for (int i = 0; i < 9; ++i) {
		std::string fn = "long" + std::to_string(i) + ".txt";
		std::string label = "#" + std::to_string(i + 1) + ":";
		check_case(label, fn);
	}

	std::cout << "3 pirmi failai su pakeistu pirmu baitu:\n";
	for (int i = 0; i < 3; ++i) {
		std::string fn = "long" + std::to_string(i) + "_start.txt";
		std::string label = "#" + std::to_string(i + 1) + ":";
		check_case(label, fn);
	}

	std::cout << "3 sekantys failai su pakeistu viduriniu baitu:\n";
	for (int i = 3; i < 6; ++i) {
		std::string fn = "long" + std::to_string(i) + "_mid.txt";
		std::string label = "#" + std::to_string(i - 3 + 1) + ":";
		check_case(label, fn);
	}

	std::cout << "3 paskutiniai failai su pakeistu paskutiniu baitu:\n";
	for (int i = 6; i < 9; ++i) {
		std::string fn = "long" + std::to_string(i) + "_end.txt";
		std::string label = "#" + std::to_string(i - 6 + 1) + ":";
		check_case(label, fn);
	}

	std::cout << "\nstrukturuoti atvejai:\n\n";
	check_case("pasikartojantys simboliai:", "struct_repeated.txt");
	check_case("pakeista tvarka - originalus tekstas:", "struct_order_original.txt");
	check_case("pakeista tvarka - pakeistos tvarkos tekstas:", "struct_order_reorder.txt");
	check_case("tarpas pradzioje:", "struct_space_leading.txt");
	check_case("tarpas pabaigoje:", "struct_space_trailing.txt");
	check_case("tekstas be newline:", "struct_newline_no.txt");
	check_case("tekstas su newline:", "struct_newline_yes.txt");

	check_case("\nutf8 simboliai be ascii (papildoma info eks. 1):", "utf8_case.txt");

	std::cout << "\nrankos vs failo ivesties patikra:\n\n";
	std::string input,filename_input;

	std::cout << "iveskite teksta, kuri norite hash'inti:\n";
	std::getline(std::cin, input);

	std::cout << "\niveskite failo varda, i kuri norite italpinti visiskai ta pati teksta:\n";
	std::getline(std::cin, filename_input);

	manual_vs_file(input, filename_input);

}