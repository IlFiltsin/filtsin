#include <gtest/gtest.h>
#include <mind/math/number.hpp>

void divNumberTest(const mind::math::Number &lhs, const mind::math::Number &rhs, const mind::math::Number &result) {
  mind::math::Number div = lhs / rhs;
  ASSERT_EQ(div,result);
}

TEST(div_test_case,div_small_1) {
  divNumberTest(0,5,0);
}
TEST(div_test_case,div_small_2) {
  divNumberTest(5,1,5);
}
TEST(div_test_case,div_small_3) {
  divNumberTest(1,5,0);
}
TEST(div_test_case,div_small_4) {
  divNumberTest(10,2,5);
}
TEST(div_test_case,div_small_5) {
  divNumberTest(-10,2,-5);
}
TEST(div_test_case,div_small_6) {
  divNumberTest(-1,5,0);
}
TEST(div_test_case,div_small_7) {
  divNumberTest(-5,-1,5);
}
TEST(div_test_case,div_small_8) {
  divNumberTest(20,-2,-10);
}
TEST(div_test_case,div_small_9) {
  divNumberTest(0,-2,0);
}

TEST(div_test_case,div_big_1) {
  divNumberTest(0,"588276072076724876827847266",0);
}
TEST(div_test_case,div_big_2) {
  divNumberTest("58396892869829489674276872486246","-482957892738758275316",-120915081310);
}
TEST(div_test_case,div_big_3) {
  divNumberTest("-1481872841897825757817825617675","-28187481782748178741",52572019498);
}
TEST(div_test_case,div_big_4) {
  divNumberTest("4872897573280758912715875715","-29838287582211371851",-163310228);
}
TEST(div_test_case,div_big_5) {
  divNumberTest("1387094781878478178578178357817857818472985718975817892873478621987654185","376782657627365717895617865615361785176552156","3681418859915524701692435228");
}
TEST(div_test_case,div_big_6) {
  divNumberTest(0,"-588276072076724876827847266",0);
}
TEST(div_test_case,div_big_7) {
  divNumberTest("-48285782787658278628624677288627","9947187589179835758175618751774672165761896",0);
}
TEST(div_test_case,div_big_8) {
  divNumberTest("-2847021758178578175781785216727","28470217581785781757817852727",-99);
}
