#ifndef UTTERM_H
#define UTTERM_H

#include "variable.h"
#include "atom.h"
#include "number.h"

//test Number.value()
TEST (Number, ctor) {
    Number number(1);
    ASSERT_EQ("1", number.value());
}
//test Number.symbol()
TEST (Number, symbol) {
    Number number(1);
    ASSERT_EQ("1", number.symbol());
}
//?- 25 = 25.
// true.
TEST (Number, matchSuccess) {
    Number number1(25);
    Number number2(25);
    ASSERT_TRUE(number1.match(number2));
}
//?- 25 = 0.
// false.
TEST (Number, matchFailureDiffValue) {
    Number number1(25);
    Number number2(0);
    ASSERT_FALSE(number1.match(number2));
}
//?- 25 = tom.
// false.
TEST (Number, matchFailureDiffConstant) {
    Number number(25);
    Atom tom("tom");
    ASSERT_FALSE(number.match(tom));
}
//?- 25 = X.
// true.
TEST (Number, matchSuccessToVar) {
    Number number(25);
    Variable X("X");
    ASSERT_TRUE(number.match(X));
}

//?- tom = 25.
// false.
TEST (Atom, matchFailureDiffConstant) {
    Atom tom("tom");
    Number number(25);
    ASSERT_FALSE(tom.match(number));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
    Atom tom("tom");
    Variable X("X");
    tom.match(X);
    ASSERT_EQ(X.value(), tom.value());
}

// ?- X = tom, tom = X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
    Variable X("X");
    Atom tom("tom");
    ASSERT_TRUE(X.match(tom));
    ASSERT_TRUE(tom.match(X));
    ASSERT_EQ(X.value(), tom.value());
}

// ?- X = jerry, tom = X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
    Variable X("X");
    Atom jerry("jerry");
    Atom tom("tom");
    ASSERT_TRUE(X.match(jerry));
    ASSERT_FALSE(tom.match(X));
}

// ?- X = 5.
// X = 5.
TEST (Variable, matchSuccessToNumber) {
    Variable X("X");
    Number number(5);
    X.match(number);
    ASSERT_EQ(X.value(), number.value());
}

// ?- X = 25, X = 100.
// false.
TEST (Variable, matchFailureToTwoDiffNumbers) {
    Variable X("X");
    Number number1(25);
    Number number2(100);
    ASSERT_TRUE(X.match(number1));
    ASSERT_FALSE(X.match(number2));
}

// ?- X = tom, X = 25.
// false.
TEST (Variable, matchSuccessToAtomThenFailureToNumber) {
    Variable X("X");
    Atom tom("tom");
    Number number(25);
    ASSERT_TRUE(X.match(tom));
    ASSERT_FALSE(X.match(number));
}
//?- tom = X, 25 = X.
// false.
TEST (Variable, matchSuccessToAtomThenFailureToNumber2) {
    Atom tom("tom");
    Variable X("X");
    Number number(25);
    ASSERT_TRUE(tom.match(X));
    ASSERT_FALSE(number.match(X));
}
//?- X = tom, X = tom.
// true.
TEST(Variable, reAssignTheSameAtom){
    Variable X("X");
    Atom tom("tom");
    ASSERT_TRUE(X.match(tom));
    ASSERT_TRUE(X.match(tom));
}
#endif