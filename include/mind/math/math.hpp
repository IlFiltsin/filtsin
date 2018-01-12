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
}

#endif
