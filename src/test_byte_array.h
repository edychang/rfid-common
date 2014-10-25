
#ifndef __EZ_RFID_TEST_BYTE_ARRAY_H__
#define __EZ_RFID_TEST_BYTE_ARRAY_H__

#include "byte_array.h"

#include <iostream>
#include <assert.h>

class byte_array_tester
{
public:
    void run_tests();

private:
    void test_constructors();
    void test_empty_clear();
    void test_const_data();
    void test_size();
    void test_to_hex_string();
    void test_sub_array();
    void test_appenders();
    void test_checksum();
};

void byte_array_tester::run_tests()
{
    test_constructors();
    test_empty_clear();
    test_const_data();
    test_size();
    test_to_hex_string();
    test_sub_array();
    test_appenders();
    test_checksum();
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

    byte_array_t ba3( "313233" );
    assert( ba3.size() == 3 );
    assert( ba3.at( 0 ) == 49 );
    assert( ba3.at( 1 ) == 50 );
    assert( ba3.at( 2 ) == 51 );
}

void byte_array_tester::test_empty_clear()
{
    byte_array_t ba( "123", 3 );
    assert( ba.empty() == false );
    ba.clear();
    assert( ba.empty() == true );
}

void byte_array_tester::test_const_data()
{
    byte_array_t ba( "123", 3 );
    const char* hp = ba.data();
    assert( *hp == 49 );
    assert( *( hp + 1 ) == 50 );
    assert( *( hp + 2 ) == 51 );
}

void byte_array_tester::test_size()
{
    byte_array_t ba( "123", 3 );
    assert( ba.size() == 3 );
    assert( ba.word_size() == 2 );
    assert( ba.dword_size() == 1 );
}

void byte_array_tester::test_to_hex_string()
{
    byte_array_t ba( "123", 3 );
    assert( ba.as_hex_string() == "313233" );
}

void byte_array_tester::test_sub_array()
{
    byte_array_t ba( "123456", 6 );
    byte_array_t nba = ba.sub_array( 3, 3 );
    assert( nba.size() == 3 );
    assert( nba.as_hex_string() == "343536" );

    byte_array_t nba1 = ba.sub_array( 3, 0 );
    assert( nba1.size() == 0 );

    byte_array_t nba2 = ba.sub_array( 7, 3 );
    assert( nba2.size() == 0 );

    byte_array_t nba3 = ba.sub_array( 3, 4 );
    assert( nba3.size() == 3 );
}

void byte_array_tester::test_appenders()
{
    byte_array_t ba;
    ba.append( 49 );
    assert( ba.size() == 1 );
    assert( ba.at( 0 ) == '1' );

    ba.append( "23", 2 );
    assert( ba.size() == 3 );
    assert( ba.at( 1 ) == '2' );
    assert( ba.at( 2 ) == '3' );

    ba.append( byte_array_t( "456", 3 ) );
    assert( ba.size() == 6 );
    assert( ba.at( 3 ) == '4' );
    assert( ba.at( 4 ) == '5' );
    assert( ba.at( 5 ) == '6' );
}

// check http://www.lammertbies.nl/comm/info/crc-calculation.html
void byte_array_tester::test_checksum()
{
    byte_array_t ba( "123456789", 9 );
    assert( ba.crc16() == 0xbb3d );
    assert( ba.checksum() == 221 );

    byte_array_t ba1( "12345678", 8 );
    assert( ba1.crc16() == 0x3c9d );
    assert( ba1.checksum() == 164 );
}

#endif
