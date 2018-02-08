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

#ifndef DIGIT_MIND
#define DIGIT_MIND

#include <mind/other/common.hpp>
#include <mind/exceptions/exception.hpp>


namespace mind {
 namespace math {
  class Digit {
  public:
   Digit() = default;
   template<typename T>
   Digit(const T &, typename std::enable_if<std::is_integral<T>::value>::type * = nullptr);
   ~Digit() = default;

   template<typename T>
   enable_if_integral<T, Digit &> operator=(const T &) noexcept(!strictMode);
   Digit &operator=(char) noexcept(!strictMode);

   friend std::ostream &operator<<(std::ostream &, const Digit &) noexcept;
   friend std::istream &operator>>(std::istream &, Digit &) noexcept(!strictMode);

   friend bool operator==(const Digit &, const Digit &) noexcept;
   friend bool operator>(const Digit &, const Digit &) noexcept;
   friend bool operator<(const Digit &, const Digit &) noexcept;
   friend bool operator>=(const Digit &, const Digit &) noexcept;
   friend bool operator<=(const Digit &, const Digit &) noexcept;
   friend bool operator!=(const Digit &, const Digit &) noexcept;

   operator char() const;
   operator int() const;

  private:
   unsigned int value;
  };

  // ##############################################################################################
  // Templates methods
  // ##############################################################################################

  template<typename T>
  Digit::Digit(const T &value, typename std::enable_if<std::is_integral<T>::value>::type *) {
   *this = value;
  }

  template<typename T>
  enable_if_integral<T, Digit &> Digit::operator=(const T &value) noexcept(!strictMode) {
   if (value < 0 || value > 9) {
    runIfStrictMode([]() { throw DigitException("Invalid digit. Use only one digit to set value."); });
    this->value = 0;
   } else {
    this->value = value;
   }
   return *this;
  }
 }
}

#endif
