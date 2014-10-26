#ifndef __EZ_RFID_TEST_BYTE_STREAM_H__
#define __EZ_RFID_TEST_BYTE_STREAM_H__

#include "byte_stream.h"

class byte_stream_tester
{
public:
    void run_tests();

private:
    void test_constructors();
    void test_read_and_write();
    void test_save_and_load();
};

void byte_stream_tester::run_tests()
{
    test_constructors();
    test_read_and_write();
    test_save_and_load();
}

void byte_stream_tester::test_constructors()
{
    basic_byte_stream stream;
}

void byte_stream_tester::test_read_and_write()
{
    basic_byte_stream stream;
    uint32_t i = 49;
    stream << i;
    byte_array_t ba = stream.c_data();
    assert(ba.size() == 4);
    uint32_t ni;
    stream >> ni;
    assert( ni == 49 );
}

class test_tag : public storable
{
public:
    test_tag() : m_success( false ), m_ts( 0 ) {}
    test_tag( bool success, const std::string plate, const long long ts ) :
        m_success( success ), m_plate( plate ), m_ts( ts ) {}
    void save( basic_byte_stream& bs ) const;
    void load( basic_byte_stream& bs );

    bool m_success;
    std::string m_plate;
    long long m_ts;
};

void test_tag::save( basic_byte_stream& bs ) const
{
    bs << m_success << m_plate << m_ts;
}

void test_tag::load( basic_byte_stream& bs )
{
    bs >> m_success >> m_plate >> m_ts;
}

void byte_stream_tester::test_save_and_load()
{
    test_tag tag( true, "À’A12345", 1002993 );
    basic_byte_stream bs;
    bs << tag;

    test_tag newtag;
    bs >> newtag;
    assert( newtag.m_success == true );
    assert( newtag.m_plate == "À’A12345" );
    assert( newtag.m_ts == 1002993 );
}

#endif // __EZ_RFID_TEST_BYTE_STREAM_H__
