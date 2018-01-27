#include <mind/math/number.hpp>

void subNumberTest(const mind::math::Number &lhs, const mind::math::Number &rhs, const mind::math::Number &result) {
  mind::math::Number sum = lhs - rhs;
  ASSERT_EQ(sum,result);
}

TEST(sub_test_case,sub_small_1) {
  subNumberTest(5,0,5);
}
TEST(sub_test_case,sub_small_2) {
  subNumberTest(0,5,-5);
}
TEST(sub_test_case,sub_small_3) {
  subNumberTest(-4,4,-8);
}
TEST(sub_test_case,sub_small_4) {
  subNumberTest(-3,-1,-2);
}
TEST(sub_test_case,sub_small_5) {
  subNumberTest(54,54,0);
}
TEST(sub_test_case,sub_small_6) {
  subNumberTest(6,-6,12);
}
TEST(sub_test_case,sub_small_7) {
  subNumberTest(6,5,1);
}
TEST(sub_test_case,sub_small_8) {
  subNumberTest(0,-5,5);
}
TEST(sub_test_case,sub_small_9) {
  subNumberTest(-6,0,-6);
}
TEST(sub_test_case,sub_small_10) {
  subNumberTest(-4,-4,0);
}
TEST(sub_test_case,sub_small_11) {
  subNumberTest(-11,-2,-9);
}
