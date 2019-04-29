#include <test_helper.hpp>
#include <filtsin/numeric/impl/w_int_arithmetic.hpp>

TEST(w_int_arithmetic_test, multiplication_of_builtin_to_builtin_uint8) {
  using arithmetic = fsn::w_int_arithmetic<uint8_t>;
  using result_t = arithmetic::multiplication_builtin_parts;

  result_t result = arithmetic::multiplication_of_builtin_to_builtin(15, 14);
  ASSERT_EQ(result.top, 0);
  ASSERT_EQ(result.low, 210);

  result = arithmetic::multiplication_of_builtin_to_builtin(210, 0);
  ASSERT_EQ(result.top, 0);
  ASSERT_EQ(result.low, 0);

  result = arithmetic::multiplication_of_builtin_to_builtin(215, 134);
  ASSERT_EQ(result.top, 112);
  ASSERT_EQ(result.low, 138);
}

TEST(w_int_arithmetic_test, multiplication_of_builtin_to_builtin_uint16) {
  using arithmetic = fsn::w_int_arithmetic<uint16_t>;
  using result_t = arithmetic::multiplication_builtin_parts;

  result_t result = arithmetic::multiplication_of_builtin_to_builtin(15000, 2);
  ASSERT_EQ(result.top, 0);
  ASSERT_EQ(result.low, 30000);
  
  result = arithmetic::multiplication_of_builtin_to_builtin(0, 34200);
  ASSERT_EQ(result.top, 0);
  ASSERT_EQ(result.low, 0);

  result = arithmetic::multiplication_of_builtin_to_builtin(17500, 11200);
  ASSERT_EQ(result.top, 2990);
  ASSERT_EQ(result.low, 47360);
}

TEST(w_int_arithmetic_test, multiplication_of_builtin_to_builtin_uint32) {
  using arithmetic = fsn::w_int_arithmetic<uint32_t>;
  using result_t = arithmetic::multiplication_builtin_parts;

  result_t result = arithmetic::multiplication_of_builtin_to_builtin(286331153ul, 3ul);
  ASSERT_EQ(result.top, 0);
  ASSERT_EQ(result.low, 858993459ul);
  
  result = arithmetic::multiplication_of_builtin_to_builtin(0ul, 4294967295ul);
  ASSERT_EQ(result.top, 0);
  ASSERT_EQ(result.low, 0);

  result = arithmetic::multiplication_of_builtin_to_builtin(1431655765ul, 4294967295ul);
  ASSERT_EQ(result.top, 1431655764ul);
  ASSERT_EQ(result.low, 2863311531ul);
}

TEST(w_int_arithmetic_test, multiplication_of_builtin_to_builtin_uint64) {
  using arithmetic = fsn::w_int_arithmetic<uint64_t>;
  using result_t = arithmetic::multiplication_builtin_parts;

  result_t result = arithmetic::multiplication_of_builtin_to_builtin(51096528416498667ull, 4ull);
  ASSERT_EQ(result.top, 0);
  ASSERT_EQ(result.low, 204386113665994668ull);
  
  result = arithmetic::multiplication_of_builtin_to_builtin(204386113665994668ull, 0);
  ASSERT_EQ(result.top, 0);
  ASSERT_EQ(result.low, 0);

  result = arithmetic::multiplication_of_builtin_to_builtin(18446744073709551615ull, 175500ull);
  ASSERT_EQ(result.top, 175499ull);
  ASSERT_EQ(result.low, 18446744073709376116ull);
}

TEST(w_int_arithmetic_test, multiplication_of_wint_to_builtin_uint8) {
  using arithmetic = fsn::w_int_arithmetic<uint8_t>;
  uint8_t data[2] = {86, 1};

  uint8_t remainder = arithmetic::multiplication_of_wint_to_builtin(data, data + 2, 130);
  ASSERT_EQ_ARRAY(data, {172, 173});
  ASSERT_EQ(remainder, 0);

  uint8_t big_value[5] = {52, 25, 192, 30, 8};
  remainder = arithmetic::multiplication_of_wint_to_builtin(big_value, big_value + 5, 254);
  ASSERT_EQ_ARRAY(big_value, {152, 1, 153, 130, 14});
  ASSERT_EQ(remainder, 8);
}

TEST(w_int_arithmetic_test, multiplication_of_wint_to_builtin_uint16) {
  using arithmetic = fsn::w_int_arithmetic<uint16_t>;
  uint16_t data[2] = {35553, 1};

  uint16_t remainder = arithmetic::multiplication_of_wint_to_builtin(data, data + 2, 345);
  ASSERT_EQ_ARRAY(data, {10553, 532});
  ASSERT_EQ(remainder, 0);

  uint16_t big_value[4] = {9794, 63170, 33345, 3};
  remainder = arithmetic::multiplication_of_wint_to_builtin(big_value, big_value + 4, 39910);
  ASSERT_EQ_ARRAY(big_value, {21836, 16280, 63403, 8964});
  ASSERT_EQ(remainder, 2);
}

TEST(w_int_arithmetic_test, multiplication_of_wint_to_builtin_uint32) {
  using arithmetic = fsn::w_int_arithmetic<uint32_t>;
  uint32_t data[2] = {1, 947ul};

  uint32_t remainder = arithmetic::multiplication_of_wint_to_builtin(data, data + 2, 14280);
  ASSERT_EQ_ARRAY(data, {14280ul, 13523160ul});
  ASSERT_EQ(remainder, 0);

  uint32_t big_value[3] = {1574288416ul, 1574288416ul, 781172736ul};
  remainder = arithmetic::multiplication_of_wint_to_builtin(big_value, big_value + 3, 4192748299ul);
  ASSERT_EQ_ARRAY(big_value, {2506847584ul, 4043668384ul, 4211557952ul});
  ASSERT_EQ(remainder, 762581047ul);
}

TEST(w_int_arithmetic_test, multiplication_of_wint_to_builtin_uint64) {
  using arithmetic = fsn::w_int_arithmetic<uint64_t>;
  uint64_t data[3] = {16370898762219913216ull, 7443093219192785366ull, 306581ull};

  uint64_t remainder = arithmetic::multiplication_of_wint_to_builtin(data, data + 3, 2442424ull);
  ASSERT_EQ_ARRAY(data, {11646333375391727616ull, 15461873325037124837ull, 748801777839ull});
  ASSERT_EQ(remainder, 0);

  uint64_t big_value[6] = {0, 0, 0, 11646333375391727616ull, 15461873325037124837ull, 748801777839ull};
  remainder = arithmetic::multiplication_of_wint_to_builtin(big_value, big_value + 6, 18446744073709551457ull);
  ASSERT_EQ_ARRAY(big_value, {0ull, 0ull, 0ull, 11354144757380022272ull, 6625436497859243360ull, 15461754265554448303ull});
  ASSERT_EQ(remainder, 748801777839);
}
