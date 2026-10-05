// V1.1:
// Pridetos rotacijos
//
//
#include "hash.hpp"

int main()
{
	std::string path, menu;

	std::cout << "1 - failo ivestis;\n2 - rankine ivestis\n3 - testai\n4 - efektyvumas v1.0\n5 - rankine ivestis su druska\n"; 
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
	//choice for v1.0 TEST RESULTS
	if (menu == "3") {
		std::cout << "\ntestavimo rezultatai\n";
		std::cout << "\n1: bet kokio ilgio ivestis bei fiksuota isvestis:\n";
		std::cout << "1) tuscia ivestis: \n";
		auto res = hash_block("");
		std::cout << to_hex(res) << "\n" << "ilgis: " << to_hex(res).size() << "\n";


		std::cout << "2) 10 simboliu ivestis: \n";
		res = hash_block("abchdjrktl");
		std::cout << to_hex(res) << "\n" << "ilgis: " << to_hex(res).size() << "\n";

		std::cout << "3) 500 simboliu ivestis: \n";
		std::string input(500, 'a');
		res = hash_block(input);
		std::cout << to_hex(res) << "\n" << "ilgis: " << to_hex(res).size() << "\n";

		//---

		std::cout << "\n2: determinizmas: 3 kartus maisoma ta pati ivestis:\n";
		std::string A = "deter bbbahd a";
		std::string B = "prprprr b";

		std::string hash1 = to_hex(hash_block(A));
		std::cout << "hash A 1: " << hash1 << "\n";

		std::string hashB = to_hex(hash_block(B));
		std::cout << "hash B: " << hashB << "\n";

		std::string hash2 = to_hex(hash_block(A));
		std::cout << "hash A 2: " << hash2 << "\n";

		if (hash1 == hash2) {
			std::cout << "\ndeterministiska!\n";
		}
		else if (hash1 == hashB) {
			std::cout << "hash a ir hash b sutampa";
		}
		else {
			std::cout << "something went wrong";
		}
	}
	//choice for v1.0 hash function effectiveness benchmark
	if (menu == "4") {
		std::cout << "\nefektyvumas su 1mln., 10mln., 100mln. random simboliu (visi su tokiu pat seed) ivestimis:\n";

		benchmark_hash_v1();
	}
	//choice for MANUAL INPUT WITH SALT
	if (menu == "5") {
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


	return 0;
}