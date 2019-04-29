#include <gtest/gtest.h>

#define ASSERT_EQ_ARRAY(actual, ...) \
  do{\
    EXPECT_TRUE(equal_array_impl(actual, __VA_ARGS__, #actual));\
  }while(0)\

template <typename T, typename F, size_t size>
testing::AssertionResult equal_array_impl(const T (&actual)[size], const F (&expected)[size], const char *actual_name) noexcept {
  for (size_t i = 0; i < size; ++i) {
    if (actual[i] != expected[i]) {
      return testing::AssertionFailure() 
              << "\n\tExpected equality of these values:\n"
              << "\t  " << actual_name << "[" << i << "]\n"
              << "\t\t  Which is: " << actual[i] << "\n"
              << "\t  expected[" << i << "]\n"
              << "\t\t  Which is: " << expected[i] << "\n";
    }
  }
  return testing::AssertionSuccess();
}