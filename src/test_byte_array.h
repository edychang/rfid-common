
#ifndef __EZ_RFID_TEST_BYTE_ARRAY_H__
#define __EZ_RFID_TEST_BYTE_ARRAY_H__

#include "byte_array.h"

#include <assert.h>

class byte_array_tester
{
public:
  void run_tests();

private:
  void test_constructors();
};

void byte_array_tester::run_tests()
{
  test_constructors();
}

void byte_array_tester::test_constructors()
{
  byte_array_t ba;
  assert( ba.empty() == true );

  byte_array_t ba1( "123", 3 );
  assert( ba1.empty() == false );
  assert( ba1.size() == 3 );
  assert( ba1.at( 0 ) == 49 );
  assert( ba1[0] == 49 );
  assert( ba1.at( 1 ) == 50 );
  assert( ba1[1] == 50 );
  assert( ba1.at( 2 ) == 51 );
  assert( ba1[2] == 51 );

  byte_array_t ba2( "123", 4 );
  assert( ba2.empty() == false );
  assert( ba2.size() == 4 );
  assert( ba2.at( 0 ) == 49 );
  assert( ba2.at( 1 ) == 50 );
  assert( ba2.at( 2 ) == 51 );
  assert( ba2.at( 3 ) == 0 );

  byte_array_t ba3("313233");
  assert( ba3.size() == 3);
  assert( ba3.at( 0 ) == 49 );
  assert( ba3.at( 1 ) == 50 );
  assert( ba3.at( 2 ) == 51 );
}

#endif
