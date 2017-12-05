#include "struct.h"
#include "iterator.h"

Iterator* Struct::createNormalIterator()
{
  return new NormalIterator<Struct>(this);
}

Iterator* Struct::createBFSIterator()
{
  return new BFSIterator<Struct>(this);
}

Iterator* Struct::createDFSIterator()
{
  return new DFSIterator<Struct>(this);
}