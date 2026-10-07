#include "experiment4.hpp"
#include "hash.hpp"
#include <chrono>

void run_experiment4(){
	std::string path = "inputs/konstitucija.txt";
	std::ifstream f(path, std::ios::binary);

	if (!f) {
		std::cerr << "KLAIDA: nepavyko atidaryti failo " << path << "\n";
		return;
	}
	std::vector<std::string> lines;
	std::string line;

	int index = 0;
	while (std::getline(f, line)) {
		// std::getline removes \n
		if(lines.size() < index) line.push_back('\n');
		lines.push_back(line);
		++index;
	}

	if (f.bad()) {
		std::cerr << "KLAIDA: nepavyko nuskaityti failo " << path << "\n";
		return;
	}

	auto data = read_data("konstitucija.txt");
	const size_t total_lines = lines.size();

	//visas failas
	std::cout << "\ndabar visas failas\n\n";
	//timer start
	auto start_file = std::chrono::steady_clock::now();
	auto result_file = hash_block(data);
	auto end_file = std::chrono::steady_clock::now();
	double seconds_file = std::chrono::duration<double>(end_file - start_file).count();

	std::cout << total_lines << " eiluciu,\n" << data.size() << " baitu, hex:\n" << to_hex(result_file) << "\n" <<
		"uztruko " << seconds_file << "s.\n----------\n";

	//n *= 2^i
	size_t i = 1;
	while (i <= total_lines) {
		std::cout << "\ndabar istrauka is " + std::to_string(i) + " eiluciu\n\n";

		size_t curr_bytes = 0;
		for (size_t j = 0; j < i; ++j) {
			curr_bytes += lines[j].size();
		}

		std::vector<uint8_t> curr_data(data.begin(), data.begin() + curr_bytes);
		auto start = std::chrono::steady_clock::now();
		auto result = hash_block(curr_data);
		auto end = std::chrono::steady_clock::now();
		double seconds = std::chrono::duration<double>(end - start).count();
		std::cout << curr_bytes << " baitu, hex:\n" << to_hex(result) << "\n" <<
			"uztruko " << seconds << "s.\n----------\n";

		if (i > total_lines / 2) break;

		i *= 2;
	}
}