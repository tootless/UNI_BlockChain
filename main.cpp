// V1.1:
// Prideta bitu rotacija
// Prideta druska
#include "hash.hpp"

int main()
{
	std::string path, menu;

	std::cout << "1 - failo ivestis;\n2 - rankine ivestis\n3 - testai\n4 - rankine ivestis su druska\n5 - efektyvumas v1.1\n";
	getline(std::cin, menu);

	//choice for FILE INPUT
	if (menu == "1") {
		std::cout << "\nfailo ivestis\n";
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
		std::cout << "\nrankine ivestis\n";
		std::cout << "ivesk teksta: ";

		std::string line;
		if (!std::getline(std::cin, line)) {
			std::cerr << "KLAIDA: nepavyko nuskaityti ivesties.\n";
			return 1;
		}

		auto result = hash_block(line); // visi papildomi dalykai (tarpai, etc.) pasilieka
		std::cout << "rezultatas: \n---\n" << to_hex(result) << "\n---\n";
	}
	//choice for MANUAL INPUT WITH SALT
	if (menu == "4") {
		std::cout << "\nrankine ivestis su druska\n";
		std::cout << "ivesk teksta: ";

		std::string line;
		if (!std::getline(std::cin, line)) {
			std::cerr << "KLAIDA: nepavyko nuskaityti ivesties.\n";
			return 1;
		}

		std::string generated_salt = salt(32); //64 char salt
		auto result = hash_block_salted(line, generated_salt);

		std::cout << "druska:    " << generated_salt << "\n";
		std::cout << "rezultatas: \n---\n" << to_hex(result) << "\n---\n";

		auto result1 = hash_block(line);
		std::cout << "be druskos rezultatas: \n---\n" << to_hex(result1) << "\n---\n";
	}
	//choice for v1.1 hash function effectiveness benchmark
	if (menu == "5") {
		std::cout << "\nefektyvumas su 1mln., 10mln., 100mln. random simboliu (visi su tokiu pat seed) ivestimis:\n";

		benchmark_hash_v1_1();
	}
	return 0;
}