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

namespace mind {
	class MindException : public std::runtime_error  {
	public:
		MindException(const std::string &str) : runtime_error(str) {}
		MindException(const char *str) : runtime_error(str) {}
	};
	class MathException : public MindException {
 public:
		MathException(const std::string &str) : MindException(str) {}
		MathException(const char *str) : MindException(str) {}
	};
	class NumberException : public MathException {
 public:
		NumberException(const std::string &str) : MathException(str) {}
		NumberException(const char *str) : MathException(str) {}
	};
	class DigitException : public MathException {
	public:
		DigitException(const std::string &str) : MathException(str) {}
		DigitException(const char *str) : MathException(str) {}
	};
}

#endif
