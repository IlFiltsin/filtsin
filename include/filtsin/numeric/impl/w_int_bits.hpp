#ifndef FILTSIN_NUMERIC_IMPL_W_INT_BITS
#define FILTSIN_NUMERIC_IMPL_W_INT_BITS

// FSN headers
#include <filtsin/numeric/impl/w_int_arithmetic.hpp>
#include <filtsin/macro/def.hpp>

namespace fsn {

 template <size_t Bits, typename Sign, typename BaseType, typename Arithmetic = w_int_arithmetic<BaseType>, class = typename std::enable_if<std::is_unsigned<BaseType>::value>::type>
 struct w_int_bits {
  
  using data_type = BaseType;
  using w_integral = Arithmetic;

  static constexpr bool is_signed = std::is_signed<Sign>::value;
  static constexpr size_t data_size = Bits / w_integral::unit_size + (Bits % w_integral::unit_size == 0 ? 0 : 1);

  /////////////////////////////////////

  /*
   * w_int save sign in data: first bit of last field set to 1 if value is negative
   * For example (data_type is 64 bit variable):
   *  value = -345
   *  data[0] = 9223372036854776153 (100....0101011001)
   *                                     51
   *  ------------------
   *  value = 345
   *  data[0] = 345 (000....0101011001)
   *                     51
  */
  static fsn_constexpr bool is_positive(const data_type (&data)[data_size]) noexcept {
   if (is_signed) {
    return (data[data_size - 1] >> (w_integral::unit_size - 1)) == 0;
   } else {
    return true;
   }
  }

  /*
   * make_positive change first bit of last unit in data to 0.
  */
  static fsn_constexpr void make_positive(data_type (&data)[data_size]) noexcept {
   static_assert(is_signed, "Can not change sign for unsigned type.");
   data[data_size - 1] ^= (static_cast<data_type>(1) << (w_integral::unit_size - 1));
  }

  /*
   * make_negative change first bit of last unit in data to 1
  */
  static fsn_constexpr void make_negative(data_type (&data)[data_size]) noexcept {
   static_assert(is_signed, "Can not change sign for unsigned type.");
   data[data_size - 1] |= (static_cast<data_type>(1) << (w_integral::unit_size - 1));
  }

  static fsn_constexpr void max(data_type (&data)[data_size]) noexcept {
   for (auto &_ : data) {
    _ = w_integral::unit_max;
   }
   if (is_signed) {
    w_int_bits<Bits,signed,BaseType>::make_positive(data);
   }
  }

  static fsn_constexpr void min(data_type (&data)[data_size]) noexcept {
   for (auto &_ : data) {
    if (is_signed) {
     _ = w_integral::unit_max;
    } else {
    _ = 0;
    }
   }
  }

  static fsn_constexpr void fill_zero(data_type (&data)[data_size], size_t start = 0) noexcept {
   for (; start < data_size; ++start) {
    data[start] = 0;
   }
  }

  template <typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
  static fsn_constexpr void fill_from_builtin(data_type (&data)[data_size], T value) noexcept {

   using unsigned_t = typename std::make_unsigned<T>::type;

   auto unsigned_value = static_cast<unsigned_t>(value);

   if (sizeof(T) * 8 > Bits) {
    unsigned_value = value & ((static_cast<T>(1) << Bits) - 1);
   }

   if (unsigned_value > w_integral::unit_max) {
    size_t index = 0;
    while (unsigned_value != 0) {
     data[index++] = unsigned_value % (static_cast<unsigned_t>(w_integral::unit_max) + 1);
     unsigned_value /= (static_cast<unsigned_t>(w_integral::unit_max) + 1);
    }
    fill_zero(data, index);
   } else {
    data[0] = unsigned_value;
    fill_zero(data, 1); // fill 0 from 1 position because in 0 we have our value
   }

   if (value < 0 && is_signed) {
    w_int_bits<Bits,signed,BaseType>::make_negative(data);
   }
  }

 };

}


#endif
