#pragma once

#include <filtsin/macro/def.hpp>
#include <algorithm>

namespace fsn {

  template <typename BaseType>
  struct w_int_fill {
    
    using data_type = BaseType;

    static fsn_constexpr void fill_zero(data_type *begin, data_type *end) noexcept {
      std::fill(begin, end, static_cast<data_type>(0));
    }

    template <typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    static fsn_constexpr void fill_from_builtin(data_type *begin, data_type *end, T value) noexcept {

      // TODO
      
    }
  };

}
