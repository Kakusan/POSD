#ifndef UTLIST_H
#define UTLIST_H

#include <string>

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"   

using std::string;

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
  List l({});
  EXPECT_EQ("[]", l.symbol());
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[496, 8128]"
TEST(List, Numbers) {
  Number n1(8128), n2(496);
  List l({&n1, &n2});

  EXPECT_EQ("[8128, 496]", l.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
  Atom a1("terence_tao"), a2("alan_mathison_turing");
  List l({&a1, &a2});

  EXPECT_EQ("[terence_tao, alan_mathison_turing]", l.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
  Variable X("X"), Y("Y");
  List l({&X, &Y});

  EXPECT_EQ("[X, Y]", l.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
  Number n(496);
  Variable X("X");
  Atom a("terence_tao"), tom("tom");
  List l({&n, &X, &a});

  EXPECT_FALSE(tom.match(l));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
  Number n(496);
  Variable X("X");
  Atom a("terence_tao"), tom("tom");
  List l({&n, &X, &a});

  EXPECT_FALSE(tom.match(l));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
  Number n(496);
  Variable X("X");
  Atom a("terence_tao");
  Struct s(Atom("s"), {&X});
  List l({&n, &X, &a});

  EXPECT_FALSE(s.match(l));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
  Number n(496);
  Variable X("X");
  Atom a("terence_tao");
  List l({&n, &X, &a});
  Variable Y("Y");

  Y.match(l);
  EXPECT_EQ(Y.value(), l.value());
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
  Number n(496);
  Variable X("X");
  Atom a("terence_tao");
  List l({&n, &X, &a});

  EXPECT_FALSE(X.match(l));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
  Number n(496);
  Variable X("X");
  Atom a("terence_tao");
  List l({&n, &X, &a});

  EXPECT_TRUE(l.match(l));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
  Number n(496);
  Variable X("X"), Y("Y");
  Atom a("terence_tao");
  List l1({&n, &X, &a});
  List l2({&n, &Y, &a});

  EXPECT_TRUE(l1.match(l2));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
  Number n1(496), n2(8128);
  Variable X("X");
  Atom a("terence_tao");
  List l1({&n1, &X, &a});
  List l2({&n1, &n2, &a});
  l1.match(l2);
  EXPECT_EQ(X.value(), n2.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
  Number n(496);
  Variable X("X"), Y("Y");
  Atom a1("terence_tao"), a2("alan_mathison_turing");
  List l1({&n, &X, &a1});
  List l2({&n, &a2, &a1});
  Y.match(l1);
  X.match(a2);
  EXPECT_EQ(Y.value(), l2.value());
  EXPECT_EQ(X.value(), a2.value());
}

// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
  Atom f("first"), s("second"), t("third");
  List l({&f, &s, &t});
  EXPECT_EQ("first", l.head()->symbol());
  EXPECT_EQ("[second, third]", l.tail()->symbol());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
  Atom f("first"), s("second"), t("third");
  List l({&f, &s, &t});
  EXPECT_EQ("second", l.tail()->head()->symbol());
  EXPECT_EQ("[third]", l.tail()->tail()->symbol());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
  Atom f("first"), s("second"), t("third");
  List l1({&f});
  List l2({&l1, &s, &t});
  EXPECT_EQ("[first]", l2.head()->symbol());
  EXPECT_EQ("[second, third]", l2.tail()->symbol());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
  Atom f("first"), s("second"), t("third");
  List l({&f, &s, &t});
  EXPECT_EQ("third", l.tail()->tail()->head()->symbol());
  EXPECT_EQ("[]", l.tail()->tail()->tail()->symbol());
}
 
// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
  List l({});
  l.head();
}

// Given there is a empty list
// When client still want to get the tail of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
  List l({});
  l.tail();
}


#endif