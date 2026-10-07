#include "experiment5.hpp"
#include "hash.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <algorithm>

// abecele: ascii simboliu intervalas nuo 33 iki 126 = 94 simboliai
// vienas ascii simbolis yra 1 baitas
const int ascii_min = 33;
const int ascii_max = 126;
const int seed = 67;

const int pair_num = 100000;
const std::vector<size_t> lengths = { 10, 100, 500, 1000 };

const int collision_examples_num = 5;

std::string rand_text(size_t len, std::mt19937& rand) {
	std::uniform_int_distribution<int> dist(ascii_min, ascii_max); //random function
	std::string s;
	s.reserve(len);
	for (size_t i = 0; i < len; ++i) {
		s += static_cast<char>(dist(rand));
	}
	return s;
}

// {a,b}, kur a!=b
std::pair<std::string, std::string> gen_pair(size_t len, std::mt19937& rand) {
	std::string a = rand_text(len, rand);
	std::string b;
	do {
		b = rand_text(len, rand);
	} while (b == a);
	return { a, b };
}

void run_length_test(size_t len, std::mt19937& rand) {
	std::cout << "dabar ilgis: " << len << " baitu (ascii simboliu)\n";

	long long collisions_per_pair = 0;

	std::unordered_map<std::string, std::vector<std::string>> grouped_inputs;
	std::unordered_set<std::string> seen_inputs;

	for (int i = 0; i < pair_num; ++i) {
		auto [a, b] = gen_pair(len, rand);

		std::string hash_a = to_hex(hash_block(a));
		std::string hash_b = to_hex(hash_block(b));

		if (hash_a == hash_b) {
			++collisions_per_pair;
		}
		if (seen_inputs.insert(a).second) { //true if new input inserted, false if already in set
			grouped_inputs[hash_a].push_back(a);
		}
		if (seen_inputs.insert(b).second) {
			grouped_inputs[hash_b].push_back(b);
		}
	}

	size_t distinct_input_count = seen_inputs.size();
	int collision_groups = 0;
	std::vector<std::vector<std::string>> collision_examples;

	for (const auto& [hex, inputs] : grouped_inputs) {
		if (inputs.size() > 1) {
			++collision_groups;
			collision_examples.push_back(inputs);
		}
	}

	long long max_pair_count = static_cast<long long>(distinct_input_count) *
		(static_cast<long long>(distinct_input_count) - 1) / 2;

	std::cout << "ascii eil. poru skaicius: " << pair_num << "\n";
	std::cout << "rastos kolizijos ilgiui " << len << ": " << collisions_per_pair << "\n";
	std::cout << "skirtingu ivesciu skaicius: " << distinct_input_count << "\n";
	std::cout << "rastos kolizijos: " << collision_groups << "\n";
	std::cout << "max poru skaicius (m*(m-1)/2): " << max_pair_count << "\n";

	if (!collision_examples.empty()) {
		for (const auto& group : collision_examples) {
			std::string shared_hash = to_hex(hash_block(group[0]));
			std::cout << "hash, bendras: " << shared_hash << "\n";
			std::cout << "ivestys: ";
			for (const auto& s : group) std::cout << "\n---" << s << "\n---";
		}
	}

	std::cout << "\n";
}

void run_structured_test() {
	std::cout << "keli strukturuoti atvejai:\n";

	std::vector<std::string> inputs;

	//tie patys simboliai skirtinga tvarka
	std::string original = "abcdefghij";
	std::string reversed(original.rbegin(), original.rend());
	std::string swapped = original;
	std::swap(swapped[0], swapped[1]);

	inputs.push_back(original);
	inputs.push_back(reversed);
	inputs.push_back(swapped);

	//pasikartojantys sablonai
	for (size_t len : lengths) {
		std::string str;
		str.reserve(len);
		while (str.size() < len) str += "ab";
		str.resize(len);
		inputs.push_back(str);
	}

	std::unordered_map<std::string, std::vector<std::string>> groups;
	for (const auto& s : inputs) {
		std::string h = to_hex(hash_block(s));
		std::cout << "input:\n---" << s << "\n---\nhash: " << h << "\n";
		groups[h].push_back(s);
	}

	int collision_count = 0;
	for (const auto& [h, group] : groups) {
		if (group.size() > 1) {
			++collision_count;
			std::cout << "kolizija rasta: \n";
			for (const auto& s : group) std::cout << "\n---- " << s << "\n---\n";
		}
	}
	if (collision_count == 0) {
		std::cout << "koliziju nera\n";
	}
	std::cout << "\n";
}

void run_experiment5() {
	std::cout << "5 eksperimentas: koliziju paieska:\n";
	std::cout << "abeceles apibrezimas: ASCII " << ascii_min << "-" << ascii_max
		<< " (" << (ascii_max - ascii_min + 1) << " simboliai)\n";
	std::cout << "poru skaicius kiekvienam ilgiui: " << pair_num << "\n\n";

	std::mt19937 rand(seed);

	for (size_t len : lengths) {
		run_length_test(len, rand);
	}

	run_structured_test();
}