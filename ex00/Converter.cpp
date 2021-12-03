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
	double dtmp;
	long tmp;
	char result;

	dtmp = std::strtod(_str.c_str(), NULL);
	if (std::isnan(dtmp) || std::isinf(dtmp)) {
		throw Converter::OverflowException();
	}
	tmp = std::strtol(_str.c_str(), NULL, 10);
	if (_str.length() == 1 and !std::isdigit(_str[0])) {
		tmp = static_cast<long>(_str[0]);
	}
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
	double dtmp;
	long tmp;
	int result;

	dtmp = std::strtod(_str.c_str(), NULL);
	if (std::isnan(dtmp) || std::isinf(dtmp)) {
		throw Converter::OverflowException();
	}
	tmp = std::strtol(_str.c_str(), NULL, 10);
	if (_str.length() == 1 and !std::isdigit(_str[0])) {
		tmp = static_cast<double>(_str[0]);
	}
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
	if (_str.length() == 1 and !std::isdigit(_str[0])) {
		result = static_cast<double>(_str[0]);
	}
	if (errno == ERANGE) {
		errno = 0;
		throw Converter::OverflowException();
	}
	return result;
}

Converter::operator double() const {
	double result;
	result = std::strtod(_str.c_str(), NULL);
	if (_str.length() == 1 and !std::isdigit(_str[0])) {
		result = static_cast<double>(_str[0]);
	}
	if (errno == ERANGE) {
		errno = 0;
		throw Converter::OverflowException();
	}
	return result;
}

void Converter::print_conversions() const {
	if (!_is_non_literal())
	{
		std::cout << "Error: Argument isn't a valid litteral." << std::endl;
		return ;
	}
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
		std::cout << std::fixed << std::setprecision(_get_precision()) << float_to_print << 'f' << std::endl;
	}
	catch (std::exception const & e) {
		std::cout << e.what() << std::endl;
	}
}

void Converter::_print_double() const {
	std::cout << "double: ";
	try {
		double double_to_print = static_cast<double>(*this);
		std::cout << std::fixed << std::setprecision(_get_precision()) << double_to_print << std::endl;
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
	if (precision == 0) {
		precision = 1;
	}
	return precision;
}

bool Converter::_is_non_literal() const {
	int non_digit = 0;

	for (unsigned long i=0; i < _str.length(); i++) {
		if (!std::isdigit(_str[i]) && !(static_cast<std::string>("ainf+-.").find(_str[i]) != std::string::npos)) {
			if (i > 0) {
				return false;
			}
			non_digit++;
		}
		if (non_digit > 1) {
			return false;
		}
	}
	return true;
}