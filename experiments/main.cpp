#include "1/experiment1.hpp"
#include "2/experiment2.hpp"
#include <iostream>
#include <string>

int main() {
	std::string input;
	std::cout << "iveskite nuo 1 - 7 atitinkamam eksperimentui atlikti";
	std::getline(std::cin, input);
	int choice = std::stoi(input);

	switch (choice)
	{
	case(1):
		run_experiment1();
		break;
	case(2):
		run_experiment2();
		break;
	default:
		std::cout << "tik nuo 1-7\n";
		break;
	}
	return 0;
}