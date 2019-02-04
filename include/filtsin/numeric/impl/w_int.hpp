#ifndef FILTSIN_NUMERIC_W_INT
#define FILTSIN_NUMERIC_W_INT

// FSN headers
#include <cstdint>
#include <cstddef>

#include <filtsin/numeric/impl/w_int_bits.hpp>

namespace fsn {

 template <size_t Bits, typename Sign, typename BaseType = w_int_bits<Bits, Sign, uint64_t>>
 class w_int {
 public:

  fsn_constexpr w_int() noexcept = default;
  template <typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
  fsn_constexpr w_int(T rhs) noexcept {
      w_bits::fill_from_builtin(data, rhs);
  }
  template <size_t Bits_, typename Sign_>
  fsn_constexpr w_int(const w_int<Bits_,Sign_> &rhs) noexcept {
  }


  template <size_t Bits_, typename Sign_>
  fsn_constexpr w_int &operator=(const w_int<Bits_,Sign_> &rhs) noexcept {}
  template <typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
  fsn_constexpr w_int &operator=(T rhs) noexcept {
   w_bits::fill_from_builtin(data, rhs);
  } 

  ~w_int() = default;

 private:

  template <size_t Bits_, typename Sign_, typename BaseType_> // BaseType?
  friend class w_int;

  using w_bits   = BaseType;
  using w_type   = typename w_bits::data_type;

  w_type data[w_bits::data_size] {0};

 };
}

#endif
