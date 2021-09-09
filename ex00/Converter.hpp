#ifndef Converter_HPP
# define Converter_HPP

# include <iostream>
# include <string>
# include <stdexcept>
# include <stdlib.h>
# include <errno.h>
# include <cctype>
# include <climits>
# include <iomanip>


class Converter {

public:
	Converter();
	Converter(std::string str);
	Converter(Converter const & original);
	virtual ~Converter();
	Converter & operator=(Converter const & rhs);

	operator char() const;
	operator int() const;
	operator float() const;
	operator double() const;

	void print_conversions() const;

	class OverflowException: public std::runtime_error {
	public:
		OverflowException();
	};

	class NonDisplayableException: public std::runtime_error {
	public:
		NonDisplayableException();
	};

private:
	std::string _str;

	void _print_char() const;
	void _print_int() const;
	void _print_float() const;
	void _print_double() const;

	int _get_precision() const;
};

#endif
