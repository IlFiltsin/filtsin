#ifndef FILTSIN_NUMERIC_W_INT_OVERFLOW_CONTROL
#define FILTSIN_NUMERIC_W_INT_OVERFLOW_CONTROL

namespace fsn {
 struct w_int_overflow {
  static bool value; // set true if last operation with overflow
 };
}

#endif
