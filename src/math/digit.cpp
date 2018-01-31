#include <mind/math/digit.hpp>

namespace mind {
    namespace math {

        Digit& Digit::operator=(char num) noexcept(!strictMode) {
        if (!isdigit(num)) {
        runIfStrictMode([]() {throw DigitException("Invalid value. Use only '0-9' to set value.");});
        this->value = 0;
        } else {
        this->value = num - '0';
        }
        return *this;
        }

        std::ostream& operator<<(std::ostream &os, const Digit &digit) noexcept {
        os << digit.value;
        return os;
        }
        std::istream& operator>>(std::istream &is, Digit &digit) noexcept(!strictMode) {
        unsigned int value;
        is >> value;
        digit = value;
        return is;
        }

        bool operator==(const Digit &digit1, const Digit &digit2) noexcept {
        return digit1.value == digit2.value;
        }
        bool operator>(const Digit &digit1, const Digit &digit2) noexcept {
        return digit1.value > digit2.value;
        }
        bool operator<(const Digit &digit1, const Digit &digit2) noexcept {
        return digit1.value < digit2.value;
        }
        bool operator>=(const Digit &digit1, const Digit &digit2) noexcept {
        return digit1.value >= digit2.value;
        }
        bool operator<=(const Digit &digit1, const Digit &digit2) noexcept {
        return digit1.value <= digit2.value;
        }
        bool operator!=(const Digit &digit1, const Digit &digit2) noexcept {
        return digit1.value != digit2.value;
        }

        Digit::operator char() const {
          return this->value + '0';
        }
        Digit::operator int() const {
          return this->value;
        }
    }

}
