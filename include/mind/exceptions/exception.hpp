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

#ifndef EXC_MIND
#define EXC_MIND

#include <stdexcept>

#define createExceptionClass(name)                        \
class name : public mind::MindException {                 \
	public:                                                  \
		name(const std::string &str) : MindException(str) {};   \
		name(const char *str) : MindException(str) {};          \
};                                                        \

namespace mind {
	class MindException : public std::runtime_error  {
	public:
		MindException(const std::string &str) : runtime_error(str) {}
		MindException(const char *str) : runtime_error(str) {}
	};
}

#endif
