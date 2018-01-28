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


#ifndef NUMBER_MIND
#define NUMBER_MIND

#include <mind/other/common.hpp>
#include <mind/math/smath.hpp>
#include <mind/exceptions/exception.hpp>
#include <mind/math/digit.hpp>

#include <string>
#include <vector>

#include <algorithm>
#include <limits>
#include <bitset>
#include <tuple>


namespace mind::math {

	class Number {
	public:
		Number() = default;
		template <typename T>
		Number(const T &, typename std::enable_if<std::is_integral<T>::value>::type* = nullptr);
		Number(const std::string &);
		Number(const char *);
		Number(const Number &);
		Number(Number &&) noexcept;
		~Number();

		template <typename T>
		enable_if_integral<T, Number&> operator=(const T &) noexcept;

		Number& operator=(const std::string &) noexcept(!strictMode);
		Number& operator=(const char *) noexcept(!strictMode);
		Number& operator=(char) noexcept(!strictMode);
		Number& operator=(const Number &) noexcept;
		Number& operator=(Number &&) noexcept;

		friend std::ostream& operator<<(std::ostream &, const Number &) noexcept;
		friend std::istream& operator>>(std::istream &, Number &) noexcept(!strictMode);

		friend bool operator==(const Number &, const Number &) noexcept;
		friend bool operator>(const Number &, const Number &) noexcept;
		friend bool operator<(const Number &, const Number &) noexcept;
		friend bool operator>=(const Number &, const Number &) noexcept;
		friend bool operator<=(const Number &, const Number &) noexcept;
		friend bool operator!=(const Number &, const Number &) noexcept;

		friend Number operator+(const Number &, const Number &) noexcept;
		friend Number operator-(const Number &, const Number &) noexcept;
		friend Number operator*(const Number &, const Number &) noexcept;
		friend Number operator/(const Number &, const Number &) noexcept(!strictMode);
		friend Number operator%(const Number &, const Number &) noexcept(!strictMode);

		template <typename T>
		enable_if_integral<T,Number> friend operator+(const Number &, const T &) noexcept;
		template <typename T>
		enable_if_integral<T,Number> friend operator-(const Number &, const T &) noexcept;
		template <typename T>
		enable_if_integral<T,Number> friend operator*(const Number &, const T &) noexcept;
		template <typename T>
		enable_if_integral<T,Number> friend operator/(const Number &, const T &) noexcept(!strictMode);
		template <typename T>
		enable_if_integral<T,Number> friend operator%(const Number &, const T &) noexcept(!strictMode);

		template <typename T>
		enable_if_integral<T,Number> friend operator+(const T &, const Number &) noexcept;
		template <typename T>
		enable_if_integral<T,Number> friend operator-(const T &, const Number &) noexcept;
		template <typename T>
		enable_if_integral<T,Number> friend operator*(const T &,const Number &) noexcept;
		template <typename T>
		enable_if_integral<T,Number> friend operator/(const T &,const Number &) noexcept(!strictMode);
		template <typename T>
		enable_if_integral<T,Number> friend operator%(const T &,const Number &) noexcept(!strictMode);

		friend Number& operator+=(Number &, const Number &) noexcept;
		friend Number& operator-=(Number &, const Number &) noexcept;
		friend Number& operator*=(Number &, const Number &) noexcept;
		friend Number& operator/=(Number &, const Number &) noexcept(!strictMode);
		friend Number& operator%=(Number &, const Number &) noexcept(!strictMode);

		template <typename T>
		enable_if_integral<T,Number&> friend operator+=(Number &,const T &) noexcept;
		template <typename T>
		enable_if_integral<T,Number&> friend operator-=(Number &,const T &) noexcept;
		template <typename T>
		enable_if_integral<T,Number&> friend operator*=(Number &, const T &) noexcept;
		template <typename T>
		enable_if_integral<T,Number&> friend operator/=(Number &, const T &) noexcept(!strictMode);

		friend Number operator++(Number &, int) noexcept;
		friend Number& operator++(Number &) noexcept;

		friend Number operator--(Number &, int) noexcept;
		friend Number& operator--(Number &) noexcept;

		friend const Number& operator+(const Number &);
		friend const Number operator-(const Number &);

		std::string getString() const noexcept;

		Number& add(const Number &) noexcept;
		template <typename T>
		enable_if_integral <T,Number&> add(const T &) noexcept;

		Number& sub(const Number &) noexcept;
		template <typename T>
		enable_if_integral <T,Number&> sub(const T &) noexcept;

		Number &mul(const Number &) noexcept;
		template <typename T>
		enable_if_integral <T,Number&> mul(const T &) noexcept;

		Number& div(const Number &) noexcept(!strictMode);
		template <typename T>
		enable_if_integral <T,Number&> div(const T &) noexcept(!strictMode);

		Number& mod(const Number &) noexcept(!strictMode);
		template <typename T>
		enable_if_integral <T,Number&> mod(const T &) noexcept(!strictMode);

		bool isEqual(const Number &) const noexcept;

		bool isLong() const noexcept;
		bool isUndefined() const noexcept;
		bool isPositive() const noexcept;
		bool isNegative() const noexcept;
		bool isZero() const noexcept;

	private:

		using vr = std::vector<primitive::ull64>;

		struct Info {
			int sign;
			vr realP;
		};

		Info *info {nullptr};

		void allocInfo() noexcept;
		void clearInfo() noexcept;

		void setValue(std::string) noexcept(!strictMode);
		void setString(const std::string &) noexcept;

		static primitive::ull64 addPrimitive(vr &, primitive::ull64, primitive::ull64 = 0) noexcept;
		static primitive::ull64 subPrimitive(vr &, primitive::ull64, primitive::ull64 = 0) noexcept;
		static primitive::ull64 mulPrimitive(vr &, primitive::ull64, primitive::ull64 = 0) noexcept;
		static primitive::ull64 divPrimitive(vr &, primitive::ull64, primitive::ull64 = 0) noexcept;

		static void addVector(vr &, const vr &) noexcept;
		static void subVector(vr &, const vr &) noexcept;
		static void mulVector(vr &, const vr &) noexcept;
		static vr   divVector(vr &, const vr &) noexcept;
		static void modVector(vr &, const vr &) noexcept;

		static std::tuple<primitive::ull64,primitive::ull64> getBitsMul(primitive::ull64, primitive::ull64) noexcept;
		static primitive::ull64 mulAddPrimitive(const vr::const_iterator &, const vr::const_iterator &, primitive::ull64, vr::iterator) noexcept;
		static primitive::ull64 mulSubPrimitive(const vr::const_iterator &, const vr::const_iterator &, primitive::ull64, vr::iterator) noexcept;
		static vr divVector2(vr &, const vr &, primitive::ull64) noexcept;
		static vr divVectorM(vr &, vr, primitive::ull64) noexcept;
		static primitive::ull64 divInvert(primitive::ull64, primitive::ull64 &, primitive::ull64 &, primitive::ull64, primitive::ull64, primitive::ull64) noexcept;
		static void addPrimitiveRemainder(primitive::ull64 &, primitive::ull64, primitive::ull64 &, primitive::ull64) noexcept;
		static void subPrimitiveRemainder(primitive::ull64 &, primitive::ull64, primitive::ull64 &, primitive::ull64, primitive::ull64) noexcept;
		static primitive::ull64 getClz(primitive::ull64) noexcept;
		static primitive::ull64 invertValue(primitive::ull64, primitive::ull64) noexcept;
		static void shiftToLeft(vr &, primitive::ull64) noexcept;

		static int cmpVector(const vr &, const vr &) noexcept;
		template <typename T>
		enable_if_integral <T,int> cmpPrimitive(const vr &, const T &) noexcept;

		static constexpr primitive::ull64 COUNT_BITS = 64;
		static constexpr primitive::ull64 HALF_BITS  = COUNT_BITS / 2;
		static constexpr primitive::ull64 RIGHT_BIT  = 1ull << (HALF_BITS);
		static constexpr primitive::ull64 BIT_MASK   = RIGHT_BIT - 1;
		static constexpr primitive::ull64 EXPONENT   = 19;
		static constexpr primitive::ull64 BASE_TEN   = 10000000000000000000ull;

	};


	// ##############################################################################################
	// 									                         Templates methods
	// ##############################################################################################

	template <typename T>
	Number::Number(const T &value, typename std::enable_if<std::is_integral<T>::value>::type *) {
		*this = value;
	}

	template <typename T>
	enable_if_integral <T, Number&> Number::operator=(const T &value) noexcept {
		this->allocInfo();
		this->clearInfo();
		this->info->realP.emplace_back(math::abs(value));
		this->info->sign = math::sgn(value);
		return *this;
	}

	template <typename T>
	enable_if_integral<T,Number> operator+(const Number &lhs, const T &value) noexcept {
		if (!lhs.isUndefined()) {
			Number result = lhs;
			return result.add(value);
		}
		return Number{};
	}
	template <typename T>
	enable_if_integral<T,Number> operator-(const Number &lhs, const T &value) noexcept {
		if (!lhs.isUndefined()) {
			Number result = lhs;
			return result.sub(value);
		}
		return Number{};
	}
	template <typename T>
	enable_if_integral<T,Number> operator*(const Number &lhs, const T &value) noexcept {
		if (!lhs.isUndefined()) {
			Number result = lhs;
			return result.mul(value);
		}
		return Number{};
	}
	template <typename T>
	enable_if_integral<T,Number> operator/(const Number &lhs, const T &value) noexcept(!strictMode) {
		if (!lhs.isUndefined()) {
			Number result = lhs;
			return result.div(value);
		}
		return Number{};
	}
	template <typename T>
	enable_if_integral<T,Number> operator%(const Number &lhs, const T &value) noexcept(!strictMode) {
		if (!lhs.isUndefined()) {
			Number result = lhs;
			return result.mod(value);
		}
		return Number{};
	}

	template <typename T>
	enable_if_integral<T,Number> operator+(const T &value, const Number &rhs) noexcept {
		return rhs + value;
	}
	template <typename T>
	enable_if_integral<T,Number> operator-(const T &value, const Number &rhs) noexcept {
		if (!rhs.isUndefined()) {
			Number result = value;
			return result.sub(rhs);
		}
		return Number{};
	}
	template <typename T>
	enable_if_integral<T,Number> operator*(const T &value,const Number &rhs) noexcept {
		return rhs * value;
	}
	template <typename T>
	enable_if_integral<T,Number> operator/(const T &value,const Number &rhs) noexcept(!strictMode) {
		if (!rhs.isUndefined()) {
			Number result = value;
			return result.div(rhs);
		}
		return Number{};
	}
	template <typename T>
	enable_if_integral<T,Number> operator%(const T &value,const Number &rhs) noexcept(!strictMode) {
		if (!rhs.isUndefined()) {
			Number result = value;
			return result.mod(rhs);
		}
		return Number{};
	}

	template <typename T>
	enable_if_integral<T,Number&> operator+=(Number &lhs,const T &value) noexcept {
		return lhs.add(value);
	}
	template <typename T>
	enable_if_integral<T,Number&> operator-=(Number &lhs,const T &value) noexcept {
		return lhs.sub(value);
	}
	template <typename T>
	enable_if_integral<T,Number&> operator*=(Number &lhs, const T &value) noexcept {
		return lhs.mul(value);
	}
	template <typename T>
	enable_if_integral<T,Number&> operator/=(Number &lhs, const T &value) noexcept(!strictMode) {
		return lhs.div(value);
	}

	template <typename T>
	enable_if_integral <T,Number&> Number::add(const T &value) noexcept {
		if (!this->isUndefined()) {
			if (this->isZero()) {
				*this = value;
			} else if ((this->isPositive() && math::sgn(value) == 1) || (this->isNegative() && math::sgn(value) == -1)) {
				primitive::ull64 remainder = Number::addPrimitive(this->info->realP,math::abs(value));
				if (remainder) {
					this->info->realP.push_back(remainder);
				}
			} else {
				switch (Number::cmpPrimitive(this->info->realP,math::abs(value))) {
					case 0:
						*this = 0;
						break;
					case -1: {
						auto copy = *this->info->realP.cbegin();
						*this->info->realP.begin() = math::abs(value);
						Number::subPrimitive(this->info->realP, copy);
						this->info->sign *= -1;
						break;
					}
					case 1:
						Number::subPrimitive(this->info->realP,math::abs(value));
						break;
				}
			}
		}
		return *this;
	}

	template <typename T>
	enable_if_integral <T,Number&> Number::sub(const T &value) noexcept {
		if (!this->isUndefined()) {
			if (this->isZero()) {
				*this = value;
				this->info->sign *= -1;
			} else if ((this->isPositive() && value > 0) || (this->isNegative() && value < 0)) {
				switch (Number::cmpPrimitive(this->info->realP,math::abs(value))) {
					case 0:
						*this = 0;
						break;
					case -1: {
						auto copy = *this->info->realP.cbegin();
						*this->info->realP.begin() = math::abs(value);
						Number::subPrimitive(this->info->realP, copy);
						this->info->sign *= -1;
						break;
					}
					case 1:
						Number::subPrimitive(this->info->realP,math::abs(value));
						break;
				}
			} else {
				auto remainder = Number::addPrimitive(this->info->realP,math::abs(value));
				if (remainder) {
					this->info->realP.push_back(remainder);
				}
			}
		}
		return *this;
	}

	template <typename T>
	enable_if_integral <T,Number&> Number::mul(const T &value) noexcept {
		if (!this->isUndefined()) {
			auto remainder = Number::mulPrimitive(this->info->realP,math::abs(value));
			if (remainder > 0) {
				this->info->realP.push_back(remainder);
			}
			this->info->sign *= math::sgn(value);
		}
		return *this;
	}

	template <typename T>
	enable_if_integral <T,Number&> Number::div(const T &value) noexcept(!strictMode) {
		if (!this->isUndefined()) {
			if (value != 0) {
				if (*this < value) {
					*this = 0;
				} else {
					Number::divPrimitive(this->info->realP, math::abs(value));
					this->info->sign *= math::sgn(value);
				}
			} else {
				runIfStrictMode([]() {throw NumberException("Invalid divider. Can't divide by zero.");});
			}
		}
		return *this;
	}

	template <typename T>
	enable_if_integral <T,Number&> Number::mod(const T &value) noexcept(!strictMode) {
		if (!this->isUndefined()) {
			if (value != 0) {
				this->info->realP = vr{Number::divPrimitive(this->info->realP,math::abs(value))};
			} else {
				runIfStrictMode([]() {throw NumberException("Invalid divider. Can't divide by zero."); });
			}
		}
		return *this;
	}

	template <typename T>
	enable_if_integral <T,int> Number::cmpPrimitive(const vr &vec, const T &value) noexcept {
		if (vec.size() == 1) {
			primitive::ull64 vectorVal = *vec.cbegin();
			if (vectorVal == value) {
				return 0;
			} else {
				if (vectorVal > value) {
					return  1;
				} else {
					return  -1;
				}
			}
		}
		return 1;
	}


}

#endif
