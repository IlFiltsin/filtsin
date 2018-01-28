#include <gtest/gtest.h>
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

TEST(sum_test_case,sum_big_1) {
  sumNumberTest(0,"5257827385723897582785236","5257827385723897582785236");
}
TEST(sum_test_case,sum_big_2) {
  sumNumberTest("5257827385723897582785236",0,"5257827385723897582785236");
}
TEST(sum_test_case,sum_big_3) {
  sumNumberTest("-5257827385723897582785236","5257827385723897582785236",0);
}
TEST(sum_test_case,sum_big_4) {
  sumNumberTest("-52578273857238975827852365","5257827385723897582785236","-47320446471515078245067129");
}
TEST(sum_test_case,sum_big_5) {
  sumNumberTest("-2589832095823098592835873267","42890358902870572876892787566","40300526807047474284056914299");
}
TEST(sum_test_case,sum_big_6) {
  sumNumberTest("423885728758178758317857815","-58928657847286287682","423885669829520911031570133");
}
TEST(sum_test_case,sum_big_7) {
  sumNumberTest("-487213751571878237581785636175611","-39827854198751832758718511","-487213791399732436333618394894122");
}
TEST(sum_test_case,sum_big_8) {
  sumNumberTest("-4821587872185781785715326",0,"-4821587872185781785715326");
}
TEST(sum_test_case,sum_big_9) {
  sumNumberTest("3768436894878782464326276","3768436894878782464326276","7536873789757564928652552");
}
TEST(sum_test_case,sum_big_10) {
  sumNumberTest("3768436894878782464326276","-376843689487878246432627526","-373075252592999463968301250");
}