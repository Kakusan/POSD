#include "variable.h"
#include "iterator.h"

Iterator<Term*>* Variable::createNormalIterator()
{
  return new NormalIterator<Term*>(this);
}

Iterator<Term*>* Variable::createBFSIterator()
{
  return new BFSIterator<Term*>(this);
}

Iterator<Term*>* Variable::createDFSIterator()
{
  return new DFSIterator<Term*>(this);
}