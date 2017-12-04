#include "struct.h"
#include "iterator.h"

Iterator * List::createIterator()
{
  return new ListIterator(this);
}