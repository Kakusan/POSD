#include "atom.h"
#include "iterator.h"

Iterator<Term*>* Atom::createNormalIterator()
{
  return new NormalIterator<Term*>(this);
}

Iterator<Term*>* Atom::createBFSIterator()
{
  return new BFSIterator<Term*>(this);
}

Iterator<Term*>* Atom::createDFSIterator()
{
  return new DFSIterator<Term*>(this);
}