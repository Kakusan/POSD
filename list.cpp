#include "list.h"
#include "iterator.h"

Iterator<Term*>* List::createNormalIterator()
{
  return new NormalIterator<Term*>(this);
}

Iterator<Term*>* List::createBFSIterator()
{
  return new BFSIterator<Term*>(this);
}

Iterator<Term*>* List::createDFSIterator()
{
  return new DFSIterator<Term*>(this);
}