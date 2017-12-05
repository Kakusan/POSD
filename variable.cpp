#include "variable.h"
#include "iterator.h"

Iterator* Variable::createNormalIterator()
{
  return new NormalIterator<Variable>(this);
}

Iterator* Variable::createBFSIterator()
{
  return new BFSIterator<Variable>(this);
}

Iterator* Variable::createDFSIterator()
{
  return new DFSIterator<Variable>(this);
}