#include <stdint.h>
#include <iostream>
#include "Data.hpp"

uintptr_t serialize(Data * ptr) {
	return reinterpret_cast<uintptr_t>(ptr);
}

Data * deserialize(uintptr_t raw) {
	return reinterpret_cast<Data *>(raw);
}

void print_data(Data * data) {
	std::cout << "\tdata.position: " << data->position << std::endl;
	std::cout << "\tdata.size: " << data->size << std::endl;
}

int main() {

	struct Data a_struct = {42,37};
	uintptr_t serialized = serialize(&a_struct);

	std::cout << "Base data: " << std::endl;
	print_data(&a_struct);
	std::cout << "Serialized pointer: " << serialized << std::endl;
	std::cout << "Deserialized data: " << std::endl;
	print_data(deserialize(serialized));

	return 0;
}
