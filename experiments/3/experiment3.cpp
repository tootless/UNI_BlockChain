#include "experiment3.hpp"
#include "hash.hpp"

void run_experiment3()
{
	std::array<std::string, 29> files = { "empty","single_a","single_b","long0","long1","long2","long3","long4","long5",
											"long6","long7","long8","long0_start","long1_start","long2_start","long3_mid","long4_mid","long5_mid","long6_end",
											"long7_end","long8_end","struct_repeated","struct_order_original","struct_order_reorder",
											"struct_space_leading","struct_space_trailing","struct_newline_no","struct_newline_yes","utf8_case" };

	std::cout << "3 eksperimentas: determinizmo testai\n\n";
	std::cout << "5 kartus is eiles tu paciu duomenu maisymas po viena faila: \n";

	for (std::string f : files) {
		f.append(".txt");

		std::cout << "\ndabar failas: " << f << "\n";
		auto data = read_data(f);
		for (int i = 0; i < 5; ++i) {
			auto res = hash_block(data);
			std::cout << "\n#" + std::to_string(i + 1) + ": " << to_hex(res) << "\n";
		}
		std::cout << "\n--------\n";
	}

	std::cout << "A B A C A C seka: \n";

	size_t a = 0, b = a + 1, c = a + 2;

	std::cout << "\ndabar failas A: " << files.at(a) << "\n";
	auto data1 = read_data(files.at(a)+".txt");
	auto resA1 = hash_block(data1);
	std::cout << "\n#A:" << to_hex(resA1) << "\n--------\n";

	std::cout << "\ndabar failas B: " << files.at(b) << "\n";
	auto data2 = read_data(files.at(b) + ".txt");
	auto resB1 = hash_block(data2);
	std::cout << "\n#B:" << to_hex(resB1) << "\n--------\n";

	std::cout << "\ndabar failas A: " << files.at(a) << "\n";
	auto data3 = read_data(files.at(a) + ".txt");
	auto resA2 = hash_block(data3);
	std::cout << "\n#A:" << to_hex(resA2) << "\n--------\n";

	std::cout << "\ndabar failas C: " << files.at(c) << "\n";
	auto data4 = read_data(files.at(c) + ".txt");
	auto resC1 = hash_block(data4);
	std::cout << "\n#C:" << to_hex(resC1) << "\n--------\n";

	std::cout << "\ndabar failas B: " << files.at(b) << "\n";
	auto data5 = read_data(files.at(b) + ".txt");
	auto resB2 = hash_block(data5);
	std::cout << "\n#B:" << to_hex(resB2) << "\n--------\n";

	std::cout << "\ndabar failas A: " << files.at(a) << "\n";
	auto data6 = read_data(files.at(a) + ".txt");
	auto resA3 = hash_block(data6);
	std::cout << "\n#A:" << to_hex(resA3) << "\n--------\n";

	std::cout << "\ndabar failas C: " << files.at(c) << "\n";
	auto data7 = read_data(files.at(c) + ".txt");
	auto resC2 = hash_block(data7);
	std::cout << "\n#C:" << to_hex(resC2) << "\n--------\n";

	if (resA1 == resA2 && resA1 == resA3 && resA2 == resA3) {
		std::cout << "\nA rezultatas deterministiskas\n";
	}
	if (resB1 == resB2) {
		std::cout << "\nB rezultatas deterministiskas\n";
	}
	if (resC1 == resC2) {
		std::cout << "\nC rezultatas deterministiskas\n";
	}
}