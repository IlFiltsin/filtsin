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
	Number pow(Number, primitive::ull64) noexcept;
	Number powm(Number, Number, const Number &) noexcept(!strictMode);
	Number powm(Number, primitive::ull64 , primitive::ull64) noexcept(!strictMode);
}

#endif
