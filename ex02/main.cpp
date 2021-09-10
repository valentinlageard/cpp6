#include <iostream>
#include "Base.hpp"
#include "ABC.hpp"
#include <cstdlib>
#include <ctime>
#include <stdexcept>

Base * generate(void) {
	int roll = rand() % 3;

	if (roll == 0) {
		return new A();
	} else if (roll == 1) {
		return new B();
	} else {
		return new C();
	}
}


void identify(Base * p) {
	std::cout << "Base pointer points to: ";
	if (dynamic_cast<A *>(p)) {
		std::cout << "A" << std::endl;
	} else if (dynamic_cast<B *>(p)) {
		std::cout << "B" << std::endl;
	} else {
		std::cout << "C" << std::endl;
	}
}


void identify(Base & p) {
	std::cout << "Base reference refers to: ";
	try {
		A & a = dynamic_cast<A &>(p);
		(void)a;
		std::cout << "A" << std::endl;
	}
	catch (std::exception const &) {}
	try {
		B & b = dynamic_cast<B &>(p);
		(void)b;
		std::cout << "B" << std::endl;
	}
	catch (std::exception const &) {}
	try {
		C & c = dynamic_cast<C &>(p);
		(void)c;
		std::cout << "C" << std::endl;
	}
	catch (std::exception const &) {}
}


int main() {
	srand (time(NULL));

	for (int i=0; i < 20; i++) {
		Base * base_ptr = generate();
		Base & base_ref = *generate();

		identify(base_ptr);
		identify(base_ref);

		delete base_ptr;
		delete &base_ref;
	}

	return 0;
}
