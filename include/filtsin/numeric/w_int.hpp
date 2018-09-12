#ifndef FILTSIN_NUMERIC_W_INT
#define FILTSIN_NUMERIC_W_INT

// FSN headers
#include <numeric/w_int_bits.hpp>
#include <numeric/w_int_overflow_control.hpp>

namespace fsn {

 template <size_t Bits, typename Sign>
 class w_int {
 public:

  __constexpr w_int() noexcept = default;
  template <typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
  __constexpr w_int(T rhs) noexcept {
   w_bits::fill_from_builtin(data,rhs);
  }
  template <size_t Bits_, typename Sign_>
  __constexpr w_int(const w_int<Bits_,Sign_> &) noexcept {}
  template <size_t Bits_, typename Sign_>
  __constexpr w_int(w_int<Bits_,Sign_> &&) noexcept {}

  template <size_t Bits_, typename Sign_>
  __constexpr w_int &operator=(const w_int<Bits_,Sign_> &rhs) noexcept {}
  template <typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
  __constexpr w_int &operator=(T rhs) noexcept {}

  void print() const {
   for (auto &v : data) {
    std::cout << v << " ";
   }
   std::cout << std::endl;
  }

  ~w_int() = default;

 private:

  template <size_t Bits_, typename Sign_>
  friend class w_int;

  using w_bits   = w_int_bits<Bits,Sign>;
  using w_type   = typename w_bits::data_type;

  w_type data[w_bits::data_size]{0};

 };
}

#endif