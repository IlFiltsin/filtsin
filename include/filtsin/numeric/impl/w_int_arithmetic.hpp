#ifndef FILTSIN_NUMERIC_W_INT_ARITHMETIC
#define FILTSIN_NUMERIC_W_INT_ARITHMETIC

#include <limits>
#include <type_traits>

#include <filtsin/macro/def.hpp>

namespace fsn {
 template<typename BaseType, class = typename std::enable_if<std::is_unsigned<BaseType>::value>::type>
 struct w_int_arithmetic {
  
  using  unit_type = BaseType;
  static constexpr unit_type unit_max   = std::numeric_limits<unit_type>::max();
  static constexpr size_t    unit_size  = sizeof(unit_type) * 8;

  template <typename T>
  struct multiplication_builtin_parts {
    T higher;
    T lower;
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
   *              ^
   *           It is sum of first 8 bits of the mul and last 8 bits of the mul2
   *     ^
   *   It is first 4 bits of the result, we know it by taking last 4 bits of the mul2 and check overflow in sum of
   *   first 8 bits of the mul and last 8 bits of the mul2
   *
   *   Result: higher is 10101100, lower is 11000010
   *
   */
  template <typename T, class = typename std::enable_if<std::is_unsigned<T>::value>::type>
  static fsn_constexpr multiplication_builtin_parts<T> multiplication_of_builtin_to_builtin(T value1, T value2) noexcept {
   constexpr size_t t_size  = sizeof(T) * 4; // (t_size * 8) / 2
   constexpr T      mask    = ((static_cast<T>(1) << t_size) - 1);

   const T lower_of_value1  = value1 & mask;
   const T higher_of_value1 = value1 >> t_size;
   const T lower_of_value2  = value2 & mask;
   const T higher_of_value2 = value2 >> t_size;

   const T ll        = lower_of_value1  * lower_of_value2;
   const T hl        = higher_of_value1 * lower_of_value2;
   const T lh        = lower_of_value1  * higher_of_value2 + (ll >> t_size) + hl;
   const T hh        = higher_of_value1 * higher_of_value2;

   const T lower  = (ll & mask) + (lh << t_size);
   const T higher = (lh >> t_size) + hh + ((lh < hl) ? (mask + 1) : 0);

   return {higher,lower};
  }

  template <typename T, class = typename std::enable_if<std::is_unsigned<T>::value>::type>
  static fsn_constexpr T multiplication_of_wint_to_builtin(T *begin, T *end, T value) {
   T remainder = 0;
   for (; begin < end; ++begin) {
    auto multiplication_of_builtin = multiplication_of_builtin_to_builtin(*begin,value);
    *begin    = multiplication_of_builtin.lower + remainder;
    remainder = ((*begin < remainder) ? 1 : 0) + multiplication_of_builtin.higher;
   }
   return remainder;
  }


 };
}

#endif
