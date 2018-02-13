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
#include <mind/math/number.hpp>

#include <algorithm>
#include <limits>
#include <bitset>

namespace mind {
 namespace math {

  Number::Number(const std::string &value) {
   this->setValue(value);
  }
  Number::Number(const char *value) {
   this->setValue(value);
  }
  Number::Number(std::initializer_list<Digit> value) {
   *this = value;
  }
  Number::Number(const Number &rhs) {
   *this = rhs;
  }
  Number::Number(Number &&rhs) = default;
  Number::~Number() = default;

  Number &Number::operator=(const std::string &value) noexcept(!strictMode) {
   this->setValue(value);
   return *this;
  }
  Number &Number::operator=(const char *value) noexcept(!strictMode) {
   this->setValue(value);
   return *this;
  }
  Number &Number::operator=(char value) noexcept(!strictMode) {
   if (isdigit(value)) {
    this->allocInfo();
    this->clearInfo();
    this->info->bits.emplace_back(value - '0');
    this->info->sign = 1;
   } else {
    runIfStrictMode([]() { throw NumberException("Invalid symbol. Use only one digit to set value."); });
   }
   return *this;
  }
  Number &Number::operator=(std::initializer_list<Digit> value) noexcept {
   std::string strValue(value.begin(), value.end());
   this->setValue(strValue);
   return *this;
  }
  Number &Number::operator=(const Number &rhs) noexcept {
   if (this != &rhs) {
    if (rhs.info != nullptr) {
     this->info = std::unique_ptr<Info>(new Info(*rhs.info));
    } else {
     this->info.reset();
    }
   }
   return *this;
  }
  Number &Number::operator=(Number &&rhs) noexcept = default;

  std::ostream &operator<<(std::ostream &os, const Number &obj) noexcept {
   os << obj.getString();
   return os;
  }
  std::istream &operator>>(std::istream &is, Number &obj) noexcept(!strictMode) {
   std::string value;
   is >> value;
   obj = value;
   return is;
  }

  bool operator==(const Number &lhs, const Number &rhs) noexcept {
   return lhs.isEqual(rhs);
  }
  bool operator>(const Number &lhs, const Number &rhs) noexcept {
   if (lhs.isUndefined() || rhs.isUndefined()) {
    return false;
   }

   if (lhs.info->sign == rhs.info->sign) {
    if (lhs.isPositive()) {
     return Number::cmpVector(lhs.info->bits, rhs.info->bits) == 1;
    } else {
     return Number::cmpVector(lhs.info->bits, rhs.info->bits) == -1;
    }
   } else {
    return lhs.info->sign > rhs.info->sign;
   }
   return false;
  }
  bool operator<(const Number &lhs, const Number &rhs) noexcept {
   if (lhs.isUndefined() || rhs.isUndefined()) {
    return false;
   }

   if (lhs.info->sign == rhs.info->sign) {
    if (lhs.isPositive()) {
     return Number::cmpVector(lhs.info->bits, rhs.info->bits) == -1;
    } else {
     return Number::cmpVector(lhs.info->bits, rhs.info->bits) == 1;
    }
   } else {
    return lhs.info->sign < rhs.info->sign;
   }
   return false;
  }
  bool operator>=(const Number &lhs, const Number &rhs) noexcept {
   return lhs > rhs || lhs == rhs;
  }
  bool operator<=(const Number &lhs, const Number &rhs) noexcept {
   return lhs < rhs || lhs == rhs;
  }
  bool operator!=(const Number &lhs, const Number &rhs) noexcept {
   return !(lhs == rhs);
  }
  Number operator+(const Number &lhs, const Number &rhs) noexcept {
   if (!lhs.isUndefined() && !rhs.isUndefined()) {
    Number result = lhs;
    return result.add(rhs);
   }
   return Number{};
  }
  Number operator-(const Number &lhs, const Number &rhs) noexcept {
   if (!lhs.isUndefined() && !rhs.isUndefined()) {
    Number result = lhs;
    return result.sub(rhs);
   }
   return Number{};
  }
  Number operator*(const Number &lhs, const Number &rhs) noexcept {
   if (!lhs.isUndefined() && !rhs.isUndefined()) {
    Number result = lhs;
    return result.mul(rhs);
   }
   return Number{};
  }
  Number operator/(const Number &lhs, const Number &rhs) noexcept(!strictMode) {
   if (!lhs.isUndefined() && !rhs.isUndefined()) {
    Number result = lhs;
    return result.div(rhs);
   }
   return Number{};
  }
  Number operator%(const Number &lhs, const Number &rhs) noexcept(!strictMode) {
   if (!lhs.isUndefined() && !rhs.isUndefined()) {
    Number result = lhs;
    return result.mod(rhs);
   }
   return Number{};
  }

  Number &operator+=(Number &lhs, const Number &rhs) noexcept {
   return lhs.add(rhs);
  }
  Number &operator-=(Number &lhs, const Number &rhs) noexcept {
   return lhs.sub(rhs);
  }
  Number &operator*=(Number &lhs, const Number &rhs) noexcept {
   return lhs.mul(rhs);
  }
  Number &operator/=(Number &lhs, const Number &rhs) noexcept(!strictMode) {
   return lhs.div(rhs);
  }
  Number &operator%=(Number &lhs, const Number &rhs) noexcept(!strictMode) {
   return lhs.mod(rhs);
  }

  Number operator++(Number &obj, int) noexcept {
   Number oldCopy = obj;
   obj += 1;
   return oldCopy;
  }
  Number &operator++(Number &obj) noexcept {
   obj += 1;
   return obj;
  }
  Number operator--(Number &obj, int) noexcept {
   Number oldCopy = obj;
   obj -= 1;
   return oldCopy;
  }
  Number &operator--(Number &obj) noexcept {
   obj -= 1;
   return obj;
  }

  const Number &operator+(const Number &obj) {
   return obj;
  }
  const Number operator-(const Number &obj) {
   Number result = obj;
   if (!result.isUndefined()) {
    result.info->sign *= -1;
   }
   return result;
  }

  std::string Number::getString() const noexcept {
   std::string result;

   if (this->isUndefined()) {
    return result;
   }

   if (this->isLong()) {

    vr bitsCopy = this->info->bits;
    primitive::tick count = bitsCopy.size();

    do {
     const primitive::ull64 partOfResult = Number::divPrimitive(bitsCopy, Number::BASE_TEN);
     result.insert(0, std::to_string(partOfResult));

     primitive::tick curSize = math::cnt(partOfResult);
     if (curSize < Number::EXPONENT) {
      for (; curSize < Number::EXPONENT; ++curSize) {
       result.insert(0, "0");
      }
     }

     if (*(bitsCopy.cbegin() + count - 1) == 0) {
      count--;
     }
    } while (count > 1);

    if (*bitsCopy.cbegin() != 0) {
     result.insert(0, std::to_string(*bitsCopy.cbegin()));
    }

   } else {
    result = std::to_string(*this->info->bits.cbegin());
   }

   if (this->info->sign == -1) {
    result.insert(0, "-");
   }

   return result;
  }

  std::vector<Digit> Number::getDigits() const noexcept {
   std::string value = this->getString();
   std::vector<Digit> digits(value.begin(), value.end());
   return digits;
  }

  Number &Number::add(const Number &value) noexcept {

   if (this->isUndefined() || value.isUndefined()) {
    this->clearInfo();
    return *this;
   }

   if (this->isZero()) {
    *this = value;
   } else if (this->info->sign == value.info->sign) {
    Number::addVector(this->info->bits, value.info->bits);
   } else switch (Number::cmpVector(this->info->bits, value.info->bits)) {
     case 0:
      *this = 0;
      break;
     case -1: {
      auto copy = this->info->bits;
      this->info->bits = value.info->bits;
      Number::subVector(this->info->bits, copy);
      this->info->sign *= -1;
      break;
     }
     case 1:
      Number::subVector(this->info->bits, value.info->bits);
      break;
    }
   return *this;
  }

  Number &Number::sub(const Number &value) noexcept {
   if (this->isUndefined() || value.isUndefined()) {
    this->clearInfo();
    return *this;
   }

   if (this->isZero()) {
    *this = value;
    this->info->sign *= -1;
   } else if (this->info->sign != value.info->sign) {
    Number::addVector(this->info->bits, value.info->bits);
   } else switch (Number::cmpVector(this->info->bits, value.info->bits)) {
     case 0:
      *this = 0;
      break;
     case -1: {
      auto copy = this->info->bits;
      this->info->bits = value.info->bits;
      Number::subVector(this->info->bits, copy);
      this->info->sign *= -1;
      break;
     }
     case 1:
      Number::subVector(this->info->bits, value.info->bits);
      break;
    }
   return *this;
  }

  Number &Number::mul(const Number &value) noexcept {
   if (this->isUndefined() || value.isUndefined()) {
    this->clearInfo();
    return *this;
   }

   if (this == &value) {
    vr vectorCopy = value.info->bits;
    Number::mulVector(this->info->bits, vectorCopy);
   } else {
    if (this->info->bits.size() >= value.info->bits.size()) {
     Number::mulVector(this->info->bits, value.info->bits);
    } else {
     vr vectorCopy = this->info->bits;
     this->info->bits = value.info->bits;
     Number::mulVector(this->info->bits, vectorCopy);
    }
   }
   this->info->sign *= value.info->sign;

   return *this;
  }

  Number &Number::div(const Number &value) noexcept(!strictMode) {

   if (this->isUndefined() || value.isUndefined()) {
    this->clearInfo();
    return *this;
   }

   if (value.isZero()) {
    runIfStrictMode([]() { throw NumberException("Invalid divider. Can't divide by zero."); });
    return *this;
   }

   if (this->isZero()) {
    return *this;
   }

   if (Number::cmpVector(this->info->bits, value.info->bits) == -1) {
    *this = 0;
   } else {
    Number::divVector(this->info->bits, value.info->bits);
    this->info->sign *= value.info->sign;
   }

   return *this;
  }

  Number &Number::mod(const Number &value) noexcept(!strictMode) {
   if (this->isUndefined() || value.isUndefined()) {
    this->clearInfo();
    return *this;
   }

   if (value.isZero()) {
    runIfStrictMode([]() { throw NumberException("Invalid divider. Can't divide by zero."); });
    return *this;
   }

   if (this->isZero()) {
    return *this;
   }

   if (this->info->bits.size() >= value.info->bits.size()) {
    Number::modVector(this->info->bits, value.info->bits);
    if (this->info->bits.size() == 1 && *this->info->bits.cbegin() == 0) {
     this->info->sign = 0;
    }
   }

   return *this;
  }

  bool Number::isEqual(const Number &obj) const noexcept {
   if (!this->isUndefined() && !obj.isUndefined()) {
    return this->info->sign == obj.info->sign && this->info->bits == obj.info->bits;
   }
   return false;
  }

  bool Number::isLong() const noexcept {
   return !this->isUndefined() && this->info->bits.size() > 1;
  }

  bool Number::isUndefined() const noexcept {
   return this->info == nullptr;
  }

  bool Number::isPositive() const noexcept {
   return !this->isUndefined() && this->info->sign == 1;
  }

  bool Number::isNegative() const noexcept {
   return !this->isUndefined() && this->info->sign == -1;
  }

  bool Number::isZero() const noexcept {
   return !this->isUndefined() && this->info->sign == 0;
  }

  void Number::allocInfo() noexcept {
   if (this->info == nullptr) {
    this->info = std::unique_ptr<Info>(new Info);
   }
  }

  void Number::clearInfo() noexcept {
   if (this->info != nullptr) {
    this->info->sign = 0;
    this->info->bits.clear();
   }
  }

  void Number::setValue(std::string value) noexcept(!strictMode) {
   int sign = 1;

   while (isspace(*value.cbegin())) {
    value.erase(value.cbegin());
   }

   if (!value.empty() && (*value.cbegin() == '+' || *value.cbegin() == '-')) {
    if (*value.cbegin() == '-') {
     sign = -1;
    }
    value.erase(value.cbegin());
   }

   while (*value.cbegin() == '0' && value.size() != 1) {
    value.erase(value.cbegin());
   }

   auto newEnd = std::remove_if(
    value.begin(),
    value.end(),
    [](const char &s) -> bool {
     return !isdigit(s);
    });

   if (newEnd != value.cend()) {
    runIfStrictMode(
     []() { throw NumberException("Invalid value. Use only '+', '-', '.', ',' and '0-9' to set value. "); });
    value.erase(newEnd, value.cend());
   }

   if (!value.empty()) {

    if (value == "0") {
     sign = 0;
    }

    this->allocInfo();
    this->setString(value);
    this->info->sign = sign;
   }
  }

  void Number::setString(const std::string &value) noexcept {

   const primitive::ull64 size = value.size();
   primitive::ull64 last = (size - 1) % Number::EXPONENT + 1;
   const primitive::ull64 allocate = (size - 1) / Number::EXPONENT + 1;
   primitive::ull64 index = 0;

   this->info->bits.resize(allocate);

   primitive::ull64 val = 0;

   for (primitive::ull64 i(0); i < last; ++i) {
    val *= 10;
    val += value[i] - '0';
   }

   *(this->info->bits.begin() + index++) = val;

   while (last < size) {
    primitive::ull64 remainder = Number::mulPrimitive(this->info->bits, Number::BASE_TEN, index);

    primitive::ull64 val = 0;

    for (primitive::ull64 end(last + Number::EXPONENT); last < end && last < size; ++last) {
     val *= 10;
     val += value[last] - '0';
    }

    remainder += Number::addPrimitive(this->info->bits, val, index);

    if (remainder != 0) {
     *(this->info->bits.begin() + index++) = remainder;
    }
   }

   if (index != allocate) {
    this->info->bits.erase(this->info->bits.begin() + index, this->info->bits.end());
   }
  }

  primitive::ull64 Number::addPrimitive(vr &vector, primitive::ull64 value, primitive::ull64 n) noexcept {
   if (n == 0) {
    n = vector.size();
   }

   primitive::ull64 remainder = value;

   for (auto it(vector.begin()), end(vector.begin() + n); it < end && remainder; ++it) {
    *it += remainder;
    remainder = (*it < remainder) ? 1 : 0;
   }

   return remainder;
  }

  primitive::ull64 Number::subPrimitive(vr &vector, primitive::ull64 value, primitive::ull64 n) noexcept {
   if (n == 0) {
    n = vector.size();
   }

   primitive::ull64 remainder = value;

   for (auto it(vector.begin()), end(vector.begin() + n); it < end && remainder; ++it) {
    primitive::ull64 isOverflow = (*it < remainder) ? 1 : 0;
    *it -= remainder;
    remainder = isOverflow;
   }

   return remainder;
  }

  primitive::ull64 Number::mulPrimitive(vr &vector, primitive::ull64 value, primitive::ull64 n) noexcept {
   if (n == 0) {
    n = vector.size();
   }

   primitive::ull64 remainder = 0;

   for (auto it(vector.begin()), end(vector.begin() + n); it < end; ++it) {
    auto resultBits = Number::getBitsMul(*it, value);
    *it = std::get<1>(resultBits) + remainder;
    remainder = (*it < remainder) ? 1 : 0;
    remainder += std::get<0>(resultBits);
   }

   return remainder;
  }

  primitive::ull64 Number::divPrimitive(vr &vector, primitive::ull64 value, primitive::ull64 n) noexcept {
   const primitive::ull64 shift = Number::getClz(value);
   const primitive::ull64 normalDivisor = value << shift;
   const primitive::ull64 invertDivisor = Number::invertValue(normalDivisor, 0);

   primitive::ull64 remainder = 0;

   if (shift != 0) {
    remainder = *vector.crbegin() >> (Number::COUNT_BITS - shift);
    Number::shiftToLeft(vector, shift);
   }

   for (auto it(vector.rbegin()), end(vector.rend() - n); it < end; ++it) {

    auto resultBits = Number::getBitsMul(remainder, invertDivisor);

    const primitive::ull64 leftCopy = std::get<1>(resultBits) + *it;
    std::get<0>(resultBits) += remainder + 1;

    if (leftCopy < std::get<1>(resultBits)) {
     std::get<0>(resultBits)++;
    }
    std::get<1>(resultBits) = leftCopy;

    remainder = *it - std::get<0>(resultBits) * normalDivisor;

    if (remainder > std::get<1>(resultBits)) {
     std::get<0>(resultBits) += std::numeric_limits<primitive::ull64>::max();
     remainder += std::numeric_limits<primitive::ull64>::max() & normalDivisor;
    }

    if (remainder >= normalDivisor) {
     remainder -= normalDivisor;
     std::get<0>(resultBits)++;
    }

    *it = std::get<0>(resultBits);

   }

   return (remainder >> shift);
  }

  void Number::addVector(vr &vector, const vr &value) noexcept {
   primitive::ull64 remainder = 0;

   auto itV = value.cbegin();
   auto endV = value.cend();

   for (auto it(vector.begin()), end(vector.end()); it < end && itV < endV; ++it, ++itV) {
    *it += *itV + remainder;
    remainder = (*it < *itV) ? 1 : 0;
   }

   if (value.size() > vector.size()) {
    vector.insert(vector.end(), value.begin() + vector.size(), value.end());
   }

   if (remainder == 1) {
    for (auto it(vector.begin() + value.size()), end(vector.end()); it < end && remainder; ++it) {
     *it += remainder;
     remainder = (*it < remainder) ? 1 : 0;
    }

    if (remainder == 1) {
     vector.emplace_back(remainder);
    }
   }
  }

  void Number::subVector(vr &vector, const vr &value) noexcept {
   primitive::ull64 remainder = 0;

   auto itV = value.cbegin();
   auto endV = value.cend();

   for (auto it(vector.begin()), end(vector.end()); it < end && itV < endV; ++it, ++itV) {
    const primitive::ull64 rhsValue = *itV + remainder;
    remainder = (*it < rhsValue) ? 1 : 0;
    *it -= rhsValue;
   }

   if (remainder == 1) {
    for (auto it(vector.begin() + value.size()), end(vector.end()); it < end && remainder; ++it) {
     *it -= remainder;
     remainder = (*it < remainder) ? 1 : 0;
    }
   }
  }

  void Number::mulVector(vr &vector, const vr &value) noexcept {
   const vr copyVector = vector;

   vector.resize(vector.size() + value.size());
   *(vector.begin() + copyVector.size()) = Number::mulPrimitive(vector, *value.cbegin(), copyVector.size());

   auto itV = value.cbegin() + 1;
   auto endV = value.cend();

   for (auto it(vector.begin() + 1), end(vector.end()); it < end && itV < endV; ++it, ++itV) {
    *(it + copyVector.size()) = Number::mulAddPrimitive(copyVector.cbegin(), copyVector.cend(), *itV, it);
   }

   while (*vector.rbegin() == 0 && vector.size() != 1) {
    vector.pop_back();
   }
  }

  Number::vr Number::divVector(vr &vector, const vr &value) noexcept {
   vr remainder;

   if (value.size() == 1) {
    remainder.emplace_back(Number::divPrimitive(vector, *value.cbegin()));
   } else {
    const primitive::ull64 shift = Number::getClz(*value.crbegin());

    if (value.size() == 2) {
     remainder = divVector2(vector, value, shift);
    } else {
     remainder = divVectorM(vector, value, shift);

     if (shift != 0) {
      primitive::ull64 bitShift = *remainder.cbegin() >> shift;

      for (auto it(remainder.begin()), end(remainder.begin() + value.size() - 1); it < end; ++it) {
       *it = bitShift | (*(it + 1) << (Number::COUNT_BITS - shift));
       bitShift = *(it + 1) >> shift;
      }

      *(remainder.begin() + value.size() - 1) = bitShift;
     }
    }
   }

   while (*vector.crbegin() == 0 && vector.size() != 1) {
    vector.pop_back();
   }

   if (remainder.size() > value.size()) {
    remainder.erase(remainder.begin() + value.size(), remainder.end());
   }

   while (*remainder.cbegin() == 0 && remainder.size() != 1) {
    remainder.pop_back();
   }

   return remainder;
  }

  void Number::modVector(vr &vector, const vr &value) noexcept {
   vector = std::move(Number::divVector(vector, value));
  }

  std::tuple<primitive::ull64, primitive::ull64>
  Number::getBitsMul(primitive::ull64 value1, primitive::ull64 value2) noexcept {
   const primitive::ull64 low32Bit1 = value1 & Number::BIT_MASK;
   const primitive::ull64 high32Bit1 = value1 >> Number::HALF_BITS;

   const primitive::ull64 low32Bit2 = value2 & Number::BIT_MASK;
   const primitive::ull64 high32Bit2 = value2 >> Number::HALF_BITS;

   primitive::ull64 pM1 = low32Bit1 * low32Bit2;
   primitive::ull64 pM2 = low32Bit1 * high32Bit2;

   primitive::ull64 pM3 = high32Bit1 * low32Bit2;
   primitive::ull64 pM4 = high32Bit1 * high32Bit2;

   pM2 += pM1 >> Number::HALF_BITS;
   pM2 += pM3;
   if (pM2 < pM3) {
    pM4 += Number::RIGHT_BIT;
   }

   const primitive::ull64 lowBit = (pM2 >> Number::HALF_BITS) + pM4;
   const primitive::ull64 highBit = (pM1 & Number::BIT_MASK) + (pM2 << Number::HALF_BITS);

   return std::make_tuple(lowBit, highBit);
  }

  primitive::ull64 Number::mulAddPrimitive(const vr::const_iterator &digitsStart, const vr::const_iterator &digitsEnd,
                                           primitive::ull64 value, vr::iterator startPos) noexcept {
   primitive::ull64 remainder = 0;

   for (auto it(digitsStart), end(digitsEnd); it < end; ++it, ++startPos) {
    auto resultBits = Number::getBitsMul(*it, value);
    std::get<1>(resultBits) += remainder;

    remainder = (std::get<1>(resultBits) < remainder) ? 1 : 0;
    remainder += std::get<0>(resultBits);

    *startPos += std::get<1>(resultBits);

    if (*startPos < std::get<1>(resultBits)) {
     remainder++;
    }
   }

   return remainder;
  }

  primitive::ull64 Number::mulSubPrimitive(const vr::const_iterator &digitsStart, const vr::const_iterator &digitsEnd,
                                           primitive::ull64 value, vr::iterator startPos) noexcept {
   primitive::ull64 remainder = 0;

   for (auto it(digitsStart), end(digitsEnd); it < end; ++it, ++startPos) {
    auto resultBits = Number::getBitsMul(*it, value);
    std::get<1>(resultBits) += remainder;

    remainder = (std::get<1>(resultBits) < remainder) ? 1 : 0;
    remainder += std::get<0>(resultBits);

    if (*startPos - std::get<1>(resultBits) > *startPos) {
     remainder++;
    }

    *startPos -= std::get<1>(resultBits);
   }

   return remainder;
  }

  Number::vr Number::divVector2(vr &dividend, const vr &divider, primitive::ull64 shift) noexcept {
   primitive::ull64 normalDivider, extraDivider;
   primitive::ull64 remainder1, remainder2;

   if (shift != 0) {
    normalDivider = (*divider.crbegin() << shift) | (*divider.cbegin() >> (Number::COUNT_BITS - shift));
    extraDivider = *divider.cbegin() << shift;

    remainder1 = *dividend.crbegin() >> (Number::COUNT_BITS - shift);

    Number::shiftToLeft(dividend, shift);
   } else {
    normalDivider = *divider.crbegin();
    extraDivider = *divider.cbegin();

    remainder1 = 0;
   }

   remainder2 = *dividend.crbegin();
   dividend.pop_back();

   const primitive::ull64 invertDivider = Number::invertValue(normalDivider, extraDivider);

   for (auto it(dividend.rbegin()), end(dividend.rend()); it < end; ++it) {
    *it = Number::divInvert(*it, remainder1, remainder2, normalDivider, extraDivider, invertDivider);
   }

   if (shift != 0) {
    remainder2 >>= shift;
    remainder2 |= remainder1 << (Number::COUNT_BITS - shift);
    remainder1 >>= shift;
   }

   return vr{remainder2, remainder1};
  }

  Number::vr Number::divVectorM(vr &dividend, vr divider, primitive::ull64 shift) noexcept {
   primitive::ull64 normalDivider, extraDivider;
   primitive::ull64 remainder1, remainder2;

   if (shift != 0) {
    normalDivider = (*divider.crbegin() << shift) | (*(divider.crbegin() + 1) >> (Number::COUNT_BITS - shift));
    extraDivider = (*divider.crbegin() << shift) | (*(dividend.crbegin() + 2) >> (Number::COUNT_BITS - shift));

    remainder1 = *dividend.crbegin() >> (Number::COUNT_BITS - shift);

    Number::shiftToLeft(dividend, shift);
    Number::shiftToLeft(divider, shift);
   } else {
    normalDivider = *divider.crbegin();
    extraDivider = *(divider.crbegin() + 1);

    remainder1 = 0;
   }

   const primitive::ull64 invertDivider = Number::invertValue(normalDivider, extraDivider);

   if (shift != 0) {
    normalDivider = *divider.crbegin();
    extraDivider = *(divider.crbegin() + 1);
   }

   primitive::ull64 index = dividend.size() - divider.size();

   vr result(index + 1, 0);

   for (auto it(dividend.rbegin()), end(dividend.rbegin() + index + 1); it < end; ++it, --index) {
    remainder2 = *it;

    if (remainder1 == normalDivider && remainder2 == extraDivider) {
     Number::mulSubPrimitive(divider.cbegin(), divider.cend(), std::numeric_limits<primitive::ull64>::max(),
                             dividend.begin() + index);

     *(result.begin() + index) = std::numeric_limits<primitive::ull64>::max();
     remainder1 = *(it + 1);
    } else {
     primitive::ull64 partResult = Number::divInvert(*(it + 1), remainder1, remainder2, normalDivider, extraDivider,
                                                     invertDivider);
     primitive::ull64 glRemainder = Number::mulSubPrimitive(divider.cbegin(), divider.cend() - 2, partResult,
                                                            dividend.begin() + index);

     const primitive::ull64 remainder2IsLess = (remainder2 < glRemainder) ? 1 : 0;
     remainder2 -= glRemainder;
     glRemainder = (remainder1 < remainder2IsLess) ? 1 : 0;
     remainder1 -= remainder2IsLess;

     *(it + 1) = remainder2;

     if (glRemainder != 0) {
      remainder1 += normalDivider;
      partResult--;

      glRemainder = 0;

      for (auto itDividend(dividend.begin()), itDivider(divider.begin()), endDivider(divider.end());
           itDivider < endDivider; ++itDividend, ++itDivider) {
       *itDividend += glRemainder;
       glRemainder = (*itDividend < glRemainder) ? 1 : 0;
       *itDividend += *itDivider;
       if (*itDividend < *itDivider) {
        glRemainder++;
       }
      }

      remainder1 += glRemainder;
     }
     *(result.begin() + index) = partResult;
    }
   }

   *(dividend.begin() + divider.size() - 1) = remainder1;

   std::swap(dividend, result);

   return result;
  }

  primitive::ull64 Number::divInvert(primitive::ull64 value, primitive::ull64 &remainder1, primitive::ull64 &remainder2,
                                     primitive::ull64 normalDivider, primitive::ull64 extraDivider,
                                     primitive::ull64 invertDivider) noexcept {
   auto resultBits1 = Number::getBitsMul(remainder1, invertDivider);

   Number::addPrimitiveRemainder(std::get<0>(resultBits1), remainder1,
                                 std::get<1>(resultBits1), remainder2);

   auto resultBits2 = Number::getBitsMul(std::get<0>(resultBits1), extraDivider);

   remainder1 = remainder2 - (std::get<0>(resultBits1) * normalDivider);
   std::get<0>(resultBits1)++;

   Number::subPrimitiveRemainder(remainder1, normalDivider,
                                 remainder2, value, extraDivider);
   Number::subPrimitiveRemainder(remainder1, std::get<0>(resultBits2),
                                 remainder2, remainder2, std::get<1>(resultBits2));

   if (remainder1 >= std::get<1>(resultBits1)) {
    Number::addPrimitiveRemainder(remainder1, normalDivider & std::numeric_limits<primitive::ull64>::max(),
                                  remainder2, extraDivider & std::numeric_limits<primitive::ull64>::max());
    std::get<0>(resultBits1) += std::numeric_limits<primitive::ull64>::max();
   }

   if (remainder1 >= normalDivider && (remainder1 > normalDivider || remainder2 >= extraDivider)) {
    Number::subPrimitiveRemainder(remainder1, normalDivider,
                                  remainder2, remainder2, extraDivider);
    std::get<0>(resultBits1)++;
   }

   return std::get<0>(resultBits1);
  }

  void Number::addPrimitiveRemainder(primitive::ull64 &save1, const primitive::ull64 addToSave1, primitive::ull64 &save2,
                                     const primitive::ull64 addToSave2) noexcept {
   save1 += addToSave1;
   if (save2 + addToSave2 < save2) {
    save1++;
   }
   save2 += addToSave2;
  }

  void Number::subPrimitiveRemainder(primitive::ull64 &save1, const primitive::ull64 subToSave1, primitive::ull64 &save2,
                                     const primitive::ull64 subToSave2, const primitive::ull64 subToSave2E) noexcept {
   save1 -= subToSave1;
   if (subToSave2 < subToSave2E) {
    save1--;
   }
   save2 = subToSave2 - subToSave2E;
  }

  primitive::ull64 Number::getClz(primitive::ull64 value) noexcept {
   std::bitset<Number::COUNT_BITS> bits = value;

   primitive::ull64 result = 0;

   for (int i(63); i > 0; --i) {
    if (bits[i] == 1) {
     break;
    } else {
     result++;
    }
   }
   return result;
  }

  primitive::ull64 Number::invertValue(primitive::ull64 value, primitive::ull64 extra) noexcept {
   // In first: get bits for value in base 32
   const primitive::ull64 lowBit = value & Number::BIT_MASK;
   const primitive::ull64 higBit = value >> Number::HALF_BITS;

   // Approximation of high half of quotient.

   primitive::ull64 appr = ~(value) / higBit;

   // Not we should to get a half-limb of invert result
   // Remainder = ((~value - (highBit * appr)) << base) + (2^base - 1), where base = BASE / 2

   primitive::ull64 remainder = ((~value - (higBit * appr)) << Number::HALF_BITS) + Number::BIT_MASK;

   primitive::ull64 templateMul = lowBit * appr;

   if (remainder < templateMul) {
    appr--;
    remainder += value;
    if (remainder < templateMul && remainder >= value) {
     appr--;
     remainder += value;
    }
   }

   remainder -= templateMul;

   // Now get low half of quotient
   // lowHalf = [r + 2^base - 1]

   templateMul = (remainder >> Number::HALF_BITS) * appr + remainder;

   primitive::ull64 lowHalf = (templateMul >> Number::HALF_BITS) + 1;

   remainder <<= Number::HALF_BITS;
   remainder += Number::BIT_MASK - (value * lowHalf);

   if (remainder >= (templateMul << Number::HALF_BITS)) {
    lowHalf--;
    remainder += value;
   }

   primitive::ull64 result = (appr << Number::HALF_BITS) + lowHalf;

   if (remainder >= value) {
    result++;
    remainder -= value;
   }

   if (extra > 0) {

    remainder = ~remainder;
    remainder += extra;

    if (remainder < extra) {
     result--;
     if (remainder >= value) {
      result--;
      remainder -= value;
     }
     remainder -= value;
    }

    auto resultBits = Number::getBitsMul(extra, result);

    remainder += std::get<0>(resultBits);
    if (remainder < std::get<0>(resultBits)) {
     result--;
     result -= ((remainder > value) | ((remainder == value) && (std::get<1>(resultBits) > extra)));
    }


   }

   return result;
  }

  void Number::shiftToLeft(vr &vector, primitive::ull64 shift) noexcept {
   primitive::ull64 bitShift = *vector.crbegin() << shift;

   for (auto it(vector.rbegin()), end(vector.rend() - 1); it < end; ++it) {
    *it = bitShift | (*(it + 1) >> (Number::COUNT_BITS - shift));
    bitShift = *(it + 1) << shift;
   }

   *vector.begin() = bitShift;
  }

  int Number::cmpVector(const vr &vec1, const vr &vec2) noexcept {
   if (vec1.size() != vec2.size()) {
    if (vec1.size() > vec2.size()) {
     return 1;
    } else {
     return -1;
    }
   }

   for (auto it(vec1.crbegin()), it2(vec2.crbegin()), end(vec1.crend()); it < end; ++it, ++it2) {
    if (*it != *it2) {
     if (*it < *it2) {
      return -1;
     } else {
      return 1;
     }
    }
   }

   return 0;
  }
 }
}
