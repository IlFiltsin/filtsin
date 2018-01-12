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
}