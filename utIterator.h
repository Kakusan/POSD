#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "atom.h"
#include "number.h"
#include "variable.h"
#include "struct.h"
#include "list.h"
#include "iterator.h"

TEST(iterator, first) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    Iterator *itStruct = s.createNormalIterator();
    
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
    ASSERT_TRUE(itStruct->isDone());
}

TEST(iterator, nested_iterator) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });

  Iterator *itStruct = s.createNormalIterator();
  itStruct->first();
  itStruct->next();

  Iterator *itStruct2 = itStruct->currentItem()->createNormalIterator();
  itStruct2->first();
  ASSERT_EQ("X", itStruct2->currentItem()->symbol());
  ASSERT_FALSE(itStruct2->isDone());
  itStruct2->next();
  ASSERT_EQ("2", itStruct2->currentItem()->symbol());
  ASSERT_FALSE(itStruct2->isDone());
  itStruct2->next();
  ASSERT_TRUE(itStruct2->isDone());
}

TEST(iterator, firstList) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });

    Iterator* itList = l.createNormalIterator();
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_TRUE(itList->isDone());
}

TEST(iterator, nullIterator){
  Number one(1);
  Iterator* it = one.createNormalIterator();
  it->first();
  ASSERT_TRUE(it->isDone());
}

TEST(iterator, nested_struct_BFSIterator) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });

  Iterator *itStruct = s.createNormalIterator();
  itStruct->first();
  ASSERT_EQ("1", itStruct->currentItem()->symbol());
  itStruct->next();
  ASSERT_EQ("t", itStruct->currentItem()->symbol());
  itStruct->next();
  ASSERT_EQ("y", itStruct->currentItem()->symbol());
  itStruct->next();
  ASSERT_EQ("x", itStruct->currentItem()->symbol());
  itStruct->next();
  ASSERT_EQ("2", itStruct->currentItem()->symbol());
  itStruct->next();
  ASSERT_TRUE(itStruct->isDone());

}



#endif