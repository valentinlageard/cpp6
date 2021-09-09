#include <iostream>
#include "Converter.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "Need a single argument." << std::endl;
		return 0;
	}
	std::string literal(argv[1]);
	Converter converter(literal);
	converter.print_conversions();
	return 0;
}
