#include <gtest/gtest.h>
  
#include "utIterator.h" 
#include "atom.cpp" 
#include "variable.cpp" 
#include "struct.cpp" 
#include "list.cpp" 
    
int main( int argc , char **argv )
{
    testing :: InitGoogleTest( &argc , argv ) ;
    return RUN_ALL_TESTS( ) ;
}
