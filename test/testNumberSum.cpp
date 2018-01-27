#include <mind/math/number.hpp>

void sumNumberTest(const mind::math::Number &lhs, const mind::math::Number &rhs, const mind::math::Number &result) {
  mind::math::Number sum = lhs + rhs;
  ASSERT_EQ(sum,result);
}

TEST(sum_test_case,sum_small_1) {
  sumNumberTest(0,5,5);
}
TEST(sum_test_case,sum_small_2) {
  sumNumberTest(6,0,6);
}
TEST(sum_test_case,sum_small_3) {
  sumNumberTest(-2,2,0);
}
TEST(sum_test_case,sum_small_4) {
  sumNumberTest(-2,1,-1);
}
TEST(sum_test_case,sum_small_5) {
  sumNumberTest(54,-54,0);
}
TEST(sum_test_case,sum_small_6) {
  sumNumberTest(10,10,20);
}
TEST(sum_test_case,sum_small_7) {
  sumNumberTest(-5,6,1);
}
TEST(sum_test_case,sum_small_8) {
  sumNumberTest(0,-5,-5);
}
TEST(sum_test_case,sum_small_9) {
  sumNumberTest(-6,0,-6);
}
TEST(sum_test_case,sum_small_10) {
  sumNumberTest(56,-54,2);
}
TEST(sum_test_case,sum_small_11) {
  sumNumberTest(13,-4,9);
}
