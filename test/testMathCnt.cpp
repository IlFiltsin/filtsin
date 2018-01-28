#include <gtest/gtest.h>
#include <mind/math/math.hpp> // number.hpp, smath.hpp

TEST(cnt_test_case,cnt_small_1) {
	int a = 2;
	ASSERT_EQ(mind::math::cnt(a),1);
} 
TEST(cnt_test_case,cnt_small_2) {
	int a = -2;
	ASSERT_EQ(mind::math::cnt(a),1);
} 
TEST(cnt_test_case,cnt_small_3) {
	int a = -248278526;
	ASSERT_EQ(mind::math::cnt(a),9);
} 
TEST(cnt_test_case,cnt_small_4) {
	int a = 0;
	ASSERT_EQ(mind::math::cnt(a),1);
} 

TEST(cnt_test_case,cnt_big_1) {
	mind::math::Number a = "428518958198587167261567177581762778";
	ASSERT_EQ(mind::math::cnt(a),36);
} 
TEST(cnt_test_case,cnt_big_2) {
	mind::math::Number a = "-428518958198587167261567177581762778";
	ASSERT_EQ(mind::math::cnt(a),36);
} 
TEST(cnt_test_case,cnt_big_3) {
	mind::math::Number a = "-428518958198587167261567177581";
	ASSERT_EQ(mind::math::cnt(a),30);
} 
TEST(cnt_test_case,cnt_big_4) {
	mind::math::Number a = "0";
	ASSERT_EQ(mind::math::cnt(a),1);
} 