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

#include <mind/math/math.hpp>

namespace mind::math {
	int sgn(const Number &obj) noexcept {
		if (obj.isPositive()) {
			return 1;
		} else if (obj.isNegative()) {
			return -1;
		} else {
			return 0;
		}
	}
	Number abs(const Number &obj) noexcept {
		if (obj.isNegative()) {
			return Number(-obj);
		} else {
			return Number(obj);
		}
	}
	primitive::tick cnt(const Number &obj) noexcept {
		std::string value;
		value = obj.getString();
		if (obj.isNegative()) {
			return value.size() - 1;
		} else {
			return value.size();
		}
	}
	Number pow(Number obj, Number power) noexcept {
		if (power == 0) {
			return 1;
		}
		Number result = 1;
		while (power > 0) {
			if (power % 2 == 1) {
				result *= obj;
			}
			obj *= obj;
			power /= 2;
		}
		return result;
	}
	Number pow(Number obj, primitive::ull64 power) noexcept {
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
	Number powm(Number obj, Number power, const Number &mod) noexcept(strictMode) {
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
			if (power % 2 == 1) {
				result *= obj;
				result %= mod;
			}
			obj *= obj;
			obj %= mod;
			power /= 2;
		}
		return result;
	}
	Number powm(Number obj, primitive::ull64 power, primitive::ull64 mod) noexcept(strictMode) {
		if (mod == 0) {
			runIfStrictMode([](){throw MathException("Invalid modulo. Modulo can not be 0.");});
			return obj;
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