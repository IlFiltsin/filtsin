/*====----------------------------------------------------------------------====
#
#                         		Mind - Math library
#
# © 2018 Ilya Filtsin
#
# This file is distributed under the Apache license 2.0.
# See COPYING for details.
#
 ====----------------------------------------------------------------------====*/


#ifndef MATH_MIND
#define MATH_MIND

#include <mind/math/number.hpp>

namespace mind::math {
	int sgn(const Number &) noexcept;
	Number abs(const Number &) noexcept;
	primitive::tick cnt(const Number &) noexcept;
	Number pow(Number, Number) noexcept(!strictMode);

	template <typename T>
	enable_if_integral <T,Number> pow(Number, T) noexcept;

	Number powm(Number, Number, const Number &) noexcept(!strictMode);

	template <typename T, typename F>
	enable_if_integral_t <T,F,Number> powm(Number, T, const F &) noexcept(!strictMode);




	// ##############################################################################################
	// Template methods
	// ##############################################################################################

	template <typename T>
	enable_if_integral <T,Number> pow(Number obj, T power) noexcept {
		if (power == 0) {
			return 1;
		}
		Number result = 1;
		while (power > 0) {
			if (power & 1) {
				result *= obj;
			}
			obj *= obj;
			power >>= 1;
		}
		return result;
	}

	template <typename T, typename F>
	enable_if_integral_t <T,F,Number> powm(Number obj, T power, const F &mod) noexcept(!strictMode) {
		if (mod == 0) {
			runIfStrictMode([](){throw MathException("Invalid modulo. Modulo can not be 0.");});
			return obj;
		}

		if (power == 0) {
			return 1;
		}

		Number result = 1;
		obj %= mod;
		while (power > 0) {
			if (power & 1) {
				result *= obj;
				result %= mod;
			}
			obj *= obj;
			obj %= mod;
			power >>= 1;
		}
		return result;
	}


}

#endif
