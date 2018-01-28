#include <iostream>

#include <mind/math/number.hpp>

int main() {

	mind::math::Number value; 			// Create empty Number
	value = '3'; 						// value = 3
	mind::math::Number value2 = 2; 		// Create Number, value2 = 2

	mind::math::Number result; 			// Create empty Number

	// Sum
	result = value + value2;		  	// result = 5
	value.add(value2);				  	// value = 5

	// Substraction
	result = value - value2;		  	// result = 3
	value2.sub(value);				 	// value2 = -3

	// Multiplication
	result = value * value2; 		  	// result = -15
	value.mul(value2);				  	// value = -15

	// Division
	result = value / value2; 		  	// result = 5
	value.div(-value2); 				// value = -5

	// Mod
	result = value2 % value; 		  	// result = -3;
	value2.mod(value); 					// value2 = -3;


	value++;  // value = -4;
	value2--; // value2 = -4;

	std::cout << value << " " << value2 << " " << result << std::endl;

	return 0;

}