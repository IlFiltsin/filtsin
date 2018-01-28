#include <gtest/gtest.h>
#include <mind/math/number.hpp>

void modNumberTest(const mind::math::Number &lhs, const mind::math::Number &rhs, const mind::math::Number &result) {
  mind::math::Number mod = lhs % rhs;
  ASSERT_EQ(mod,result);
}

TEST(mod_test_case,mod_small_1) {
  modNumberTest(0,5,0);
} 
TEST(mod_test_case,mod_small_2) {
  modNumberTest(6,5,1);
} 
TEST(mod_test_case,mod_small_3) {
  modNumberTest(-12,5,-2);
} 
TEST(mod_test_case,mod_small_4) {
  modNumberTest(12,5,2);
} 
TEST(mod_test_case,mod_small_5) {
  modNumberTest(13,-4,1);
} 
TEST(mod_test_case,mod_small_6) {
  modNumberTest(-13,-4,-1);
} 
TEST(mod_test_case,mod_small_7) {
  modNumberTest(0,-5,0);
} 
TEST(mod_test_case,mod_small_8) {
  modNumberTest(5,-5,0);
} 
TEST(mod_test_case,mod_small_9) {
  modNumberTest(-5,-5,0);
} 
TEST(mod_test_case,mod_small_10) {
  modNumberTest(3,4,3);
} 
TEST(mod_test_case,mod_small_11) {
  modNumberTest(-3,-5,-3);
} 

TEST(mod_test_case,mod_big_1) {
  modNumberTest(0,"58275807287682786782786782786726",0);
} 
TEST(mod_test_case,mod_big_2) {
  modNumberTest("578738678276872626246827682786","4818740718569716765155","785649032707067033121");
} 
TEST(mod_test_case,mod_big_3) {
  modNumberTest("-3825728578278362767128616","2827816741675681785615","-2520343532840992977136");
} 
TEST(mod_test_case,mod_big_4) {
  modNumberTest("-916347261873628881993761","-198347572582857896276514536","-916347261873628881993761");
} 
TEST(mod_test_case,mod_big_5) {
  modNumberTest("2847021758178578175781785216727","2847021758178578175781785216727",0);
} 
TEST(mod_test_case,mod_big_6) {
  modNumberTest("-2847021758178578175781785216727","2847021758178578175781785216727",0);
} 
TEST(mod_test_case,mod_big_7) {
  modNumberTest("2847021758178578175781785216727","-2847021758178578175781785216727",0);
} 
TEST(mod_test_case,mod_big_8) {
  modNumberTest("-2847021758178578175781785216727","-2847021758178578175781785216727",0);
} 
TEST(mod_test_case,mod_big_9) {
  modNumberTest("-2847021758178578175781785216727","29847185781757817852727","-7805243216843948842165");
}
TEST(mod_test_case,mod_big_10) {
  modNumberTest("14812816476187268717257615672","14812816476187268717257615672215","14812816476187268717257615672");
}
TEST(mod_test_case,mod_big_11) {
  modNumberTest("-14812816476187268717257615672","14812816476187268717257615672215","-14812816476187268717257615672");
}