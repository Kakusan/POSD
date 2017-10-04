#ifndef UTNUMBER_H
#define UTNUMBER_H  
#include "number.h"
#include "atom.h"


TEST(Number, 1) {
  Number number(1);
  ASSERT_EQ(1, number.symbol());
}

TEST(Number, match_1_and_2) {
  Number number1(1);
  Number number2(2);
  EXPECT_FALSE(number1.match(number2));
  EXPECT_TRUE(number1.match(number1));
}

#endif
