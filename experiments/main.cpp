#include "1/experiment1.hpp"
#include <iostream>
#include <string>

int main() {
	std::string choice;
	std::cout << "1 - 1 eksperimentas\n";
	std::getline(std::cin, choice);

	if (choice == "1") {
		run_experiment1();
	}
	return 0;
}