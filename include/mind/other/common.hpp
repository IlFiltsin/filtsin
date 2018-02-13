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


#ifndef COMMON_MIND
#define COMMON_MIND

#include <type_traits>
#include <cstddef>

namespace mind {

	#if defined(MIND_STRICT)
		constexpr bool strictMode = true;
	#else
		constexpr bool strictMode = false;
	#endif

	namespace primitive {
		using ul64   = unsigned long;
		using l64    = long;
		using ull64  = unsigned long long;
		using ll64   = long long;
		using tick   = size_t;
	}

	void runIfStrictMode(void (*)());
	void runIfNotStrictMode(void (*)());

	template <typename T, typename R>
	using enable_if_integral = typename std::enable_if<std::is_integral<T>::value && !std::is_same<T,char>::value,R>::type;

	template <typename T, typename F, typename R>
	using enable_if_integral_t = typename std::enable_if<std::is_integral<T>::value && !std::is_same<T,char>::value && std::is_integral<F>::value && !std::is_same<F,char>::value,R>::type;


}

#endif
