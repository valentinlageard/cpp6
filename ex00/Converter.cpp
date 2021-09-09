#include "Converter.hpp"

Converter::Converter():
	_str("0")
{}

Converter::Converter(std::string str):
	_str(str)
{}

Converter::Converter(Converter const & original):
	_str(original._str)
{}

Converter::~Converter() {}

Converter & Converter::operator=(Converter const & rhs) {
	if (this == &rhs) {
		return *this;
	}
	_str = rhs._str;
	return *this;
}

Converter::operator char() const {
	long tmp;
	char result;

	tmp = std::strtol(_str.c_str(), NULL, 10);
	if (tmp < CHAR_MIN || tmp > CHAR_MAX || errno == ERANGE) {
		errno = 0;
		throw Converter::OverflowException();
	}
	result = static_cast<char>(tmp);
	if (!std::isprint(result)) {
		throw Converter::NonDisplayableException();
	}
	return result;
}

Converter::operator int() const {
	long tmp;
	int result;

	tmp = std::strtol(_str.c_str(), NULL, 10);
	if (tmp < INT_MIN || tmp > INT_MAX || errno == ERANGE) {
		errno = 0;
		throw Converter::OverflowException();
	}
	result = static_cast<int>(tmp);
	return result;
}

Converter::operator float() const {
	float result;
	result = std::strtof(_str.c_str(), NULL);
	if (errno == ERANGE) {
		errno = 0;
		throw Converter::OverflowException();
	}
	return result;
}

Converter::operator double() const {
	double result;
	result = std::strtod(_str.c_str(), NULL);
	if (errno == ERANGE) {
		errno = 0;
		throw Converter::OverflowException();
	}
	return result;
}

void Converter::print_conversions() const {
	_print_char();
	_print_int();
	_print_float();
	_print_double();
}

Converter::OverflowException::OverflowException():
	std::runtime_error("impossible")
{}

Converter::NonDisplayableException::NonDisplayableException():
	std::runtime_error("Non displayable")
{}

void Converter::_print_char() const {
	std::cout << "char: ";
	try {
		char char_to_print = static_cast<char>(*this);
		std::cout << "'" <<  char_to_print << "'" << std::endl;
	}
	catch (std::exception const & e) {
		std::cout << e.what() << std::endl;
	}
}

void Converter::_print_int() const {
	std::cout << "int: ";
	try {
		int int_to_print = static_cast<int>(*this);
		std::cout << int_to_print << std::endl;
	}
	catch (std::exception const & e) {
		std::cout << e.what() << std::endl;
	}
}

void Converter::_print_float() const {
	std::cout << "float: ";
	try {
		float float_to_print = static_cast<float>(*this);
		std::cout << std::setprecision(_get_precision()) << float_to_print << std::endl;
	}
	catch (std::exception const & e) {
		std::cout << e.what() << std::endl;
	}
}

void Converter::_print_double() const {
	std::cout << "double: ";
	try {
		double double_to_print = static_cast<double>(*this);
		std::cout << std::setprecision(_get_precision()) << double_to_print << std::endl;
	}
	catch (std::exception const & e) {
		std::cout << e.what() << std::endl;
	}
}

int Converter::_get_precision() const {
	int i = 0;
	int precision = 0;
	while (_str[i] && _str[i] != '.') {
		++i;
	}
	++i;
	while (_str[i] && std::isdigit(_str[i])) {
		++i;
		++precision;
	}
	return precision;
}
