#include <gtest/gtest.h>
  
#include "utIterator.h" 
#include "struct.cpp" 
#include "list.cpp" 

int main( int argc , char **argv )
{
    testing :: InitGoogleTest( &argc , argv ) ;
    return RUN_ALL_TESTS( ) ;
}
