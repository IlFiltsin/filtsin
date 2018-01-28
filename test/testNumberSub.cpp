#include <gtest/gtest.h>
#include <mind/math/number.hpp>

void subNumberTest(const mind::math::Number &lhs, const mind::math::Number &rhs, const mind::math::Number &result) {
  mind::math::Number sub = lhs - rhs;
  ASSERT_EQ(sub,result);
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

TEST(sub_test_case,sub_big_1) {
  subNumberTest(0,"5257827385723897582785236","-5257827385723897582785236");
}
TEST(sub_test_case,sub_big_2) {
  subNumberTest("5257827385723897582785236",0,"5257827385723897582785236");
}
TEST(sub_test_case,sub_big_3) {
  subNumberTest("-5257827385723897582785236","-5257827385723897582785236",0);
}
TEST(sub_test_case,sub_big_4) {
  subNumberTest("-52578273857238975827852365","5257827385723897582785236","-57836101242962873410637601");
}
TEST(sub_test_case,sub_big_5) {
  subNumberTest("-2589832095823098592835873267","-42890358902870572876892787566","40300526807047474284056914299");
}
TEST(sub_test_case,sub_big_6) {
  subNumberTest("423885728758178758317857815","-58928657847286287682","423885787686836605604145497");
}
TEST(sub_test_case,sub_big_7) {
  subNumberTest("-487213751571878237581785636175611","39827854198751832758718511","-487213791399732436333618394894122");
}
TEST(sub_test_case,sub_big_8) {
  subNumberTest("-4821587872185781785715326",0,"-4821587872185781785715326");
}
TEST(sub_test_case,sub_big_9) {
  subNumberTest("3768436894878782464326276","3768436894878782464326276",0);
}
TEST(sub_test_case,sub_big_10) {
  subNumberTest("3768436894878782464326276","37684368924878782464326276","-33915932030000000000000000");
}