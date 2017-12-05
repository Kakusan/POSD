#ifndef ITERATOR_H
#define ITERATOR_H

#include <typeinfo>
#include "struct.h"
#include "list.h"

class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual Term* currentItem() const = 0;
  virtual bool isDone() const = 0;
};

template<class T> 
class NormalIterator : public Iterator {
public:
  friend class List;
  friend class Struct;
  friend class Number;
  
  void first() { _index = 0; }

  void next() { _index++; }

  Term* currentItem() const { 
    if(typeid(T) == typeid(Struct))
      return _t->args(_index);
    else if(typeid(T) == typeid(List))
      return _t->elements()->at(_index);
    else 
      return nullptr;
  }

  bool isDone() const { 
    if(typeid(T) == typeid(Struct))
      return _index >= _t->arity();
    else if(typeid(T) == typeid(List))
      return _index >= _t->elements()->size();
    else 
      return true;
   }

private:
  NormalIterator(T *t): _index(0), _t(t) {}
  int _index;
  T* _t;
};

// class NullIterator : public Iterator{
// public:
//   NullIterator(Term *n){}
//   void first(){}
//   void next(){}
//   Term* currentItem() const{
//       return nullptr;
//   }
//   bool isDone() const {
//     return true;
//   }

// };

// class StructIterator : public Iterator {
// public:
//   friend class Struct;
  
//   void first() {
//     _index = 0;
//   }

//   Term* currentItem() const {
//     return _s->args(_index);
//   }

//   bool isDone() const {
//     return _index >= _s->arity();
//   }

//   void next() {
//     _index++;
//   }
// private:
//   StructIterator(Struct *s): _index(0), _s(s) {}
//   int _index;
//   Struct* _s;
// };

// class ListIterator : public Iterator {
// public:
//   friend class List;

//   void first() {
//     _index = 0;
//   }

//   Term* currentItem() const {
//     return _list->elements()->at(_index);
//   }

//   bool isDone() const {
//     return _index >= _list->elements()->size();
//   }

//   void next() {
//     _index++;
//   }
// private:
//   ListIterator(List *list) : _index(0), _list(list) {}
//   int _index;
//   List *_list;
// };
#endif