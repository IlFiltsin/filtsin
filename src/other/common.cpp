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

#include <mind/other/common.hpp>

namespace mind {

	void runIfStrictMode (void (*fun)()) {
		if (strictMode) {
			fun();
		}
	}
	void runIfNotStrictMode(void (*fun)()) {
		if (!strictMode) {
			fun();
		}
	}

}