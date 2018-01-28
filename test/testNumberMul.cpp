#include <gtest/gtest.h>
#include <mind/math/number.hpp>

void mulNumberTest(const mind::math::Number &lhs, const mind::math::Number &rhs, const mind::math::Number &result) {
  mind::math::Number mul = lhs * rhs;
  ASSERT_EQ(mul,result);
}

TEST(mul_test_case,mul_small_1) {
  mulNumberTest(5,0,0);
}
TEST(mul_test_case,mul_small_2) {
  mulNumberTest(0,5,0);
}
TEST(mul_test_case,mul_small_3) {
  mulNumberTest(5,2,10);
}
TEST(mul_test_case,mul_small_4) {
  mulNumberTest(5,-2,-10);
}
TEST(mul_test_case,mul_small_5) {
  mulNumberTest(-5,2,-10);
}
TEST(mul_test_case,mul_small_6) {
  mulNumberTest(5,2,10);
}
TEST(mul_test_case,mul_small_7) {
  mulNumberTest(2,5,10);
}
TEST(mul_test_case,mul_small_8) {
  mulNumberTest(-5,-5,25);
}
TEST(mul_test_case,mul_small_9) {
  mulNumberTest(-5,0,0);
}
TEST(mul_test_case,mul_small_10) {
  mulNumberTest(0,-5,0);
}

TEST(mul_test_case,mul_big_1) {
  mulNumberTest(0,"59037690829869482986289627732742",0);
}
TEST(mul_test_case,mul_big_2) {
  mulNumberTest("59037690829869482986289627732742",0,0);
}
TEST(mul_test_case,mul_big_3) {
  mulNumberTest("58928690289068928498692776237","59037690829869482986289627732742","3479013798295183532586807492208426468999412302374335844451854");
}
TEST(mul_test_case,mul_big_4) {
  mulNumberTest("-428587237867823761652136","59037690829869482986289627732742","-25302800842868309718945529843049609544919037953781436912");
}
TEST(mul_test_case,mul_big_5) {
  mulNumberTest("6854829357817857151363421316","-59037690829869482986289627732742","-404693296318363422098021605039003318320361948005825193928472");
}
TEST(mul_test_case,mul_big_6) {
  mulNumberTest("-50205295090905295092525","-48147187258178975841651","2417243744093950910507781204791167181793758775");
}
TEST(mul_test_case,mul_big_7) {
  mulNumberTest(0,"-59037690829869482986289627732742",0);
}
TEST(mul_test_case,mul_big_8) {
  mulNumberTest("-59037690829869482986289627732742",0,0);
}