#include "atom.h"
#include "iterator.h"

Iterator* Atom::createNormalIterator()
{
  return new NormalIterator<Atom>(this);
}

Iterator* Atom::createBFSIterator()
{
  return new BFSIterator<Atom>(this);
}

Iterator* Atom::createDFSIterator()
{
  return new DFSIterator<Atom>(this);
}