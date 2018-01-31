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

namespace mind {
    namespace math {
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
        Number pow(Number obj, Number power) noexcept(!strictMode) {
            if (power.isNegative()) {
                runIfStrictMode([](){throw MathException("Can not pow to negative power.");});
                return obj;
            }
            if (power.isZero()) {
                return 1;
            }
            Number result = 1;
            while (power.isPositive()) {
                if (power % 2 == 1) {
                    result *= obj;
                }
                obj *= obj;
                power /= 2;
            }
            return result;
        }
        Number powm(Number obj, Number power, const Number &mod) noexcept(!strictMode) {
            if (mod.isZero()) {
                runIfStrictMode([](){throw MathException("Invalid mod. Mod can not be 0.");});
                return obj;
            }
            if (power.isZero()) {
                return 1;
            }
            Number result = 1;
            obj %= mod;
            while (power.isPositive()) {
                if (power % 2 == 1) {
                    result *= obj;
                    result %= mod;
                }
                obj *= obj;
                obj %= mod;
                power /= 2;
            }
            return result;
        }
    }
}
