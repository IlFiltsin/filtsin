#include <gtest/gtest.h>
#include <mind/math/math.hpp> // number.hpp, smath.hpp

TEST(pow_test_case,pow_1) {
	mind::math::Number a = "428518958198587167261567177581762778";
	mind::math::Number power = 2;
	ASSERT_EQ(mind::math::pow(a,power),"183628497535602496013633823769649549484204398286229276388723341866277284");
} 
TEST(pow_test_case,pow_2) {
	mind::math::Number a = "428518958198587167261567177581762778";
	ASSERT_EQ(mind::math::pow(a,2),"183628497535602496013633823769649549484204398286229276388723341866277284");
} 
TEST(pow_test_case,pow_3) {
	mind::math::Number a = "428518958198587167261567177581762778";
	mind::math::Number power = 0;
	ASSERT_EQ(mind::math::pow(a,power),1);
} 
TEST(pow_test_case,pow_4) {
	mind::math::Number a = "428518958198587167261567177581762778";
	ASSERT_EQ(mind::math::pow(a,0),1);
}
TEST(pow_test_case,pow_5) {
	mind::math::Number a = "428518958198587167261567177581762778";
	mind::math::Number power = 1;
	ASSERT_EQ(mind::math::pow(a,power),a);
}  
TEST(pow_test_case,pow_6) {
	mind::math::Number a = "428518958198587167261567177581762778";
	ASSERT_EQ(mind::math::pow(a,1),a);
} 


TEST(pow_test_case,powm_1) {
	mind::math::Number a = "428518958198587167261567177581762778";
	mind::math::Number power = 2;
	mind::math::Number mod = 5;
	ASSERT_EQ(mind::math::powm(a,power,mod),4);
} 
TEST(pow_test_case,powm_2) {
	mind::math::Number a = "428518958198587167261567177581762778";
	mind::math::Number power = 2;
	ASSERT_EQ(mind::math::powm(a,power,5),4);
} 
TEST(pow_test_case,powm_3) {
	mind::math::Number a = "428518958198587167261567177581762778";
	ASSERT_EQ(mind::math::powm(a,2,5),4);
} 
TEST(pow_test_case,powm_4) {
	mind::math::Number a = "428518958198587167261567177581762778";
	mind::math::Number power = 2;
	mind::math::Number mod = -5;
	ASSERT_EQ(mind::math::powm(a,power,mod),4);
} 
TEST(pow_test_case,powm_5) {
	mind::math::Number a = "428518958198587167261567177581762778";
	mind::math::Number power = 2;
	ASSERT_EQ(mind::math::powm(a,power,-5),4);
} 
TEST(pow_test_case,powm_6) {
	mind::math::Number a = "428518958198587167261567177581762778";
	ASSERT_EQ(mind::math::powm(a,2,-5),4);
} 
TEST(pow_test_case,powm_7) {
	mind::math::Number a = "428518958198587167261567177581762778";
	mind::math::Number power = 0;
	mind::math::Number mod = 11;
	ASSERT_EQ(mind::math::powm(a,power,mod),1);
} 
TEST(pow_test_case,powm_8) {
	mind::math::Number a = "428518958198587167261567177581762778";
	mind::math::Number power = 0;
	mind::math::Number mod = 11;
	ASSERT_EQ(mind::math::powm(a,0,mod),1);
} 
TEST(pow_test_case,powm_9) {
	mind::math::Number a = "3";
	mind::math::Number power = 2;
	mind::math::Number mod = 10;
	ASSERT_EQ(mind::math::powm(a,power,mod),9);
} 
TEST(pow_test_case,powm_10) {
	mind::math::Number a = "3";
	mind::math::Number mod = 10;
	ASSERT_EQ(mind::math::powm(a,2,mod),9);
} 
TEST(pow_test_case,powm_11) {
	mind::math::Number a = "3";
	ASSERT_EQ(mind::math::powm(a,2,10),9);
} 