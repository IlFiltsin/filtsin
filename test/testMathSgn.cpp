#include <gtest/gtest.h>
#include <mind/math/math.hpp> // number.hpp, smath.hpp


TEST(sgn_test_case,sgn_small_1) {
	int a = 2;
	ASSERT_EQ(mind::math::sgn(a),1);
} 
TEST(sgn_test_case,sgn_small_2) {
	int a = 0;
	ASSERT_EQ(mind::math::sgn(a),0);
} 
TEST(sgn_test_case,sgn_small_3) {
	int a = -2;
	ASSERT_EQ(mind::math::sgn(a),-1);
} 

TEST(sgn_test_case,sgn_big_1) {
	mind::math::Number a = "375827857287687287856177581561875766";
	ASSERT_EQ(a.isPositive(),true);
	ASSERT_EQ(mind::math::sgn(a),1);
} 
TEST(sgn_test_case,sgn_big_2) {
	mind::math::Number a = "-375827857287687287856177581561875766";
	ASSERT_EQ(a.isNegative(),true);
	ASSERT_EQ(mind::math::sgn(a),-1);
} 
TEST(sgn_test_case,sgn_big_3) {
	mind::math::Number a = "0";
	ASSERT_EQ(a.isZero(),true);
	ASSERT_EQ(mind::math::sgn(a),0);
} 
