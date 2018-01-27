#include <gtest/gtest.h>

#include "testNumberSum.cpp"
#include "testNumberSub.cpp"

int main(int argc, char **argv) {
 ::testing::InitGoogleTest(&argc,argv);
 return RUN_ALL_TESTS();
}
