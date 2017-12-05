#include "list.h"
#include "iterator.h"

Iterator* List::createNormalIterator()
{
  return new NormalIterator<List>(this);
}

Iterator* List::createBFSIterator()
{
  return new BFSIterator<List>(this);
}

Iterator* List::createDFSIterator()
{
  return new DFSIterator<List>(this);
}