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

#ifndef SMATH_MIND
#define SMATH_MIND

#include <mind/other/common.hpp>
#include <mind/exceptions/exception.hpp>

namespace mind::math {

	template <typename T>
	enable_if_integral <T,int> sgn(const T &) noexcept;
	template <typename T>
	enable_if_integral <T,T> abs(const T &) noexcept;
	template <typename T>
	enable_if_integral <T,primitive::tick> cnt(T) noexcept;

	// ##############################################################################################
	// 									                             Templates methods
	// ##############################################################################################


	template <typename T>
	enable_if_integral <T,int>
	sgn(const T &value) noexcept {
		if (value < 0) {
			return -1;
		} else if (value == 0) {
			return 0;
		} else {
			return 1;
		}
	}

	template <typename T>
	enable_if_integral <T,T>
	abs(const T &value) noexcept {
		if (value < 0) {
			return -value;
		} else {
			return value;
		}
	}

	template <typename T>
	enable_if_integral <T,primitive::tick>
	cnt(T value) noexcept {
		primitive::tick result = 0;

		do {
			result++;
			value /= 10;
		} while (value);

		return result;
	}

}

#endif