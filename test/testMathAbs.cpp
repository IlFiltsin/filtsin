#include <gtest/gtest.h>
#include <mind/math/math.hpp> // number.hpp, smath.hpp


TEST(abs_test_case,abs_small_1) {
	int a = 2;
	ASSERT_EQ(mind::math::abs(a),2);
} 
TEST(abs_test_case,abs_small_2) {
	int a = 0;
	ASSERT_EQ(mind::math::abs(a),0);
} 
TEST(abs_test_case,abs_small_3) {
	int a = -2;
	ASSERT_EQ(mind::math::abs(a),2);
} 

TEST(abs_test_case,sgn_big_1) {
	mind::math::Number a = "375827857287687287856177581561875766";
	ASSERT_EQ(mind::math::abs(a),a);
} 
TEST(abs_test_case,abs_big_2) {
	mind::math::Number a = "-375827857287687287856177581561875766";
	ASSERT_EQ(mind::math::abs(a),-a);
} 
TEST(abs_test_case,abs_big_3) {
	mind::math::Number a = "0";
	ASSERT_EQ(mind::math::abs(a),0);
} 
