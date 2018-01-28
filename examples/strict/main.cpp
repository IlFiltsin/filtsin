#include <iostream>

#include <mind/math/math.hpp> // includes number.hpp

// Use -DMIND_STRICT = ON when cmake for strict mode
// Use -DMIND_STRICT for compilation

int main() {

	mind::math::Number value;

	#if defined(MIND_STRICT)
		std::cout << "STRICT" << std::endl;
	#else
		std::cout << "No-strict" << std::endl;
	#endif

	std::cout << mind::strictMode << std::endl;

	do {
		try {
			std::cin >> value;
		} catch (mind::NumberException &e) {
			std::cout << "Mind error input for value! Msg: " << e.what() << std::endl;
		}
	} while (value.isUndefined());

	value = mind::math::abs(value); // return asbolute value


	mind::math::Number value2;

	do {
		try {
			std::cin >> value2;
		} catch (mind::NumberException &e) {
			std::cout << "Mind error input for value2! Msg: " << e.what() << std::endl;
		}
	} while (value2.isUndefined());

	std::cout << value << " + " << value2 << " = " << (value + value2) << std::endl;
	std::cout << value << " - " << value2 << " = " << (value - value2) << std::endl;
	std::cout << value << " * " << value2 << " = " << (value * value2) << std::endl;

	try {
		std::cout << value << " / " << value2 << " = " << (value / value2) << std::endl;
	} catch (mind::NumberException &e) {
		std::cout << "Mind error! Msg: " << e.what() << std::endl;
	}

	try {
		std::cout << value << " mod " << value2 << " = " << (value % value2) << std::endl;
	} catch (mind::NumberException &e) {
		std::cout << "Mind error! Msg: " << e.what() << std::endl;
	}

	return 0;
}