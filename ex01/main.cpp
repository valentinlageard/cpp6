#include <stdint.h>
#include <iostream>
#include "Data.hpp"

uintptr_t serialize(Data * ptr) {
	return reinterpret_cast<uintptr_t>(ptr);
}

Data * deserialize(uintptr_t raw) {
	return &(reinterpret_cast<Data>(raw));
}

int main(int argc, char **argv) {

	return 0;
}
