#ifndef FILTSIN_NUMERIC_IMPL_W_INT_ARITHMETIC
#define FILTSIN_NUMERIC_IMPL_W_INT_ARITHMETIC

#include <limits>
#include <type_traits>

#include <filtsin/macro/def.hpp>

namespace fsn {

 template<typename BaseType, class = typename std::enable_if<std::is_unsigned<BaseType>::value>::type>
 struct w_int_arithmetic {
  
  using unit_type = BaseType;
  static constexpr unit_type unit_max   = std::numeric_limits<unit_type>::max();
  static constexpr size_t    unit_size  = sizeof(unit_type) * 8; // size in bits

  struct multiplication_builtin_parts {
    unit_type top;
    unit_type low;
  };

  /*
   * Multiplication of two numbers that can give overflow
   * Save result as 2 numbers with T type as {higher;lower} one number in binary form
   *
   * For example (sizeof(T) = 1),
   *  value1 = 234 (11101010b)
   *  value2 = 189 (10111101b)
   *
   *               1110 1010
   *               1011 1101
   *               ---------
   *               1110 | 1010   <-- mul = 11101010 * 1101
   *              00000 | 000
   *             111010 | 10
   *            1110101 | 0
   *            ------------
   *           10111110 | 0010   <-- It is last 4 bits of result, we know it by taking last 4 bits of the mul
   *           -------------
   *           11101010          <-- mul2 = 11101010 * 1011
   *       1 | 101010
   *      00 | 000000
   *     111 | 01010
   *          --------------
   *    1010 | 11001100 | 0010
   *      ^        ^
   *      |        |
   *      |    It is sum of first 8 bits of the mul and last 8 bits of the mul2
   *      |
   *   It is first 4 bits of the result, we know it by taking last 4 bits of the mul2 and check overflow in sum of
   *   first 8 bits of the mul and last 8 bits of the mul2
   *
   *   Result: top is 10101100, low is 11000010
   *
   */
  static fsn_constexpr multiplication_builtin_parts multiplication_of_builtin_to_builtin(unit_type value1, unit_type value2) noexcept {
   constexpr size_t t_size     = sizeof(unit_type) * 4; // (t_size * 8) / 2
   constexpr unit_type mask    = (static_cast<unit_type>(1) << t_size) - 1;

   const unit_type lower_of_value1  = static_cast<unit_type>(value1 & mask);
   const unit_type higher_of_value1 = static_cast<unit_type>(value1 >> t_size);
   const unit_type lower_of_value2  = static_cast<unit_type>(value2 & mask);
   const unit_type higher_of_value2 = static_cast<unit_type>(value2 >> t_size);

   const unit_type ll  = static_cast<unit_type>(lower_of_value1  * lower_of_value2);
   const unit_type hl  = static_cast<unit_type>(higher_of_value1 * lower_of_value2);
   const unit_type lh  = static_cast<unit_type>(lower_of_value1  * higher_of_value2 + (ll >> t_size) + hl);
   const unit_type hh  = static_cast<unit_type>(higher_of_value1 * higher_of_value2);

   const unit_type low  = static_cast<unit_type>((ll & mask) + (lh << t_size));
   const unit_type top = static_cast<unit_type>((lh >> t_size) + hh + ((lh < hl) ? (mask + 1) : 0));
   return {top, low};
  }

  static fsn_constexpr unit_type multiplication_of_wint_to_builtin(unit_type *begin, unit_type *end, unit_type value) {
   unit_type remainder = 0;
   for (; begin < end; ++begin) {
    auto multiplication_of_builtin = multiplication_of_builtin_to_builtin(*begin, value);
    *begin    = static_cast<unit_type>(multiplication_of_builtin.low + remainder);
    remainder = static_cast<unit_type>((*begin < remainder) + multiplication_of_builtin.top);
   }
   return remainder;
  }


 };
}

#endif
