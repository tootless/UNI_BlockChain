// V0.1

#include "hash.hpp"
#include <iomanip>
#include <fstream>
#include <sstream>

std::string to_hex(const std::array<uint32_t, state_wcount>& state) {
	std::ostringstream oss;
	oss << std::hex << std::nouppercase << std::setfill('0');
	for (uint32_t w : state) {
		oss << std::setw(8) << w;
	}
	return oss.str();
}

int main()
{
	std::string path, menu;

	std::cout << "1 - failo ivestis;\n2 - rankine ivestis\n"; getline(std::cin, menu);

	//choice for FILE INPUT
	if (menu == "1") {
		std::cout << "\n---failo ivestis---\n";
		std::cout << "\nivesk failo path: "; getline(std::cin, path);

		std::ifstream file(path, std::ios::binary); //ios::binary, tik baitai skaitomi
		if (!file) {
			std::cerr << "KLAIDA: nepavyko atidaryti failo " << path << "\n";
			return 1;
		}

		//file data into iterator
		std::vector<uint8_t> data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

		if (file.bad()) {
			std::cerr << "KLAIDA: nepavyko nuskaityti failo " << path << "\n";
			return 1; //break
		}

		std::cout << "perskaityta: " << data.size() << " baitu\n";
		auto result = hash_block(data);
		std::cout << "rezultatas: \n---\n" << to_hex(result) << "\n---\n";
	}
	//choice for MANUAL INPUT
	if (menu == "2") {
		std::cout << "\n---rankine ivestis---\n";
		std::cout << "(\"ENTER\" nera itrauktas i maisuojamus baitus\n";
		std::cout << "ivesk teksta: ";

		std::string line;
		if (!std::getline(std::cin, line)) {
			std::cerr << "KLAIDA: nepavyko nuskaityti ivesties.\n";
			return 1;
		}

		auto result = hash_block(line); // visi papildomi dalykai (tarpai, etc.) pasilieka
		std::cout << "rezultatas: \n---\n" << to_hex(result) << "\n---\n";
	}

	system("cls");
	return 0;
}