//RFID Relevant Application Common Libraries
//Copyright (C) 2014 Edward Zhang

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "byte_array.h"
#include <algorithm>

const std::string LOOKUP = "0123456789ABCDEF";

std::size_t hex_char_to_int( const char input )
{
    std::size_t found = LOOKUP.find( toupper( input ) );

    if ( found != std::string::npos )
    {
        return found;
    }

    throw std::string( "Invalid hex char" );
}

/* only to be used to align on a power of 2 boundary */
std::size_t align( std::size_t size, std::size_t boundary )
{
    return ( ( size / boundary ) + ( ( size % boundary == 0 ) ? 0 : 1 ) ) * boundary;
}

byte_array_t::byte_array_t( const std::string hex )
{
    assert( hex.length() % 2 == 0 );
    std::size_t len = hex.length() / 2;

    for ( std::size_t i = 0; i < len; i++ )
    {
        m_vec.push_back(
            static_cast<char>( ( hex_char_to_int( hex[i * 2] ) << 4 )
                               + hex_char_to_int( hex[i * 2 + 1] ) ) );
    }
}

std::string byte_array_t::as_hex_string() const
{
    std::vector<char> tmp;
    tmp.reserve( size() * 2 );

    for ( std::size_t i = 0, s = size(); i < s; i++ )
    {
        tmp.push_back( LOOKUP[m_vec[i] >> 4] );
        tmp.push_back( LOOKUP[m_vec[i] & 0x0f] );
    }

    return std::string( tmp.begin(), tmp.end() );
}

std::size_t byte_array_t::word_size() const
{
    return align( size(), 2 ) / 2;
}

std::size_t byte_array_t::dword_size() const
{
    return align( size(), 4 ) / 4;
}

// following algorithm comes from:
// http://stackoverflow.com/questions/10564491/function-to-calculate-a-crc16-checksum
#define CRC16 0x8005
uint16_t gen_crc16( const char *data, std::size_t size )
{
    uint16_t out = 0;
    int bits_read = 0, bit_flag;

    /* Sanity check: */
    if ( data == NULL )
        return 0;

    while ( size > 0 )
    {
        bit_flag = out >> 15;

        /* Get next bit: */
        out <<= 1;
        out |= ( *data >> bits_read ) & 1; // item a) work from the least significant bits

        /* Increment bit counter: */
        bits_read++;

        if ( bits_read > 7 )
        {
            bits_read = 0;
            data++;
            size--;
        }

        /* Cycle check: */
        if ( bit_flag )
            out ^= CRC16;

    }

    // item b) "push out" the last 16 bits
    int i;

    for ( i = 0; i < 16; ++i )
    {
        bit_flag = out >> 15;
        out <<= 1;

        if ( bit_flag )
            out ^= CRC16;
    }

    // item c) reverse the bits
    uint16_t crc = 0;
    i = 0x8000;
    int j = 0x0001;

    for ( ; i != 0; i >>= 1, j <<= 1 )
    {
        if ( i & out )
            crc |= j;
    }

    return crc;
}

uint16_t byte_array_t::crc16() const
{
    return gen_crc16( &m_vec[0], m_vec.size() );
}

uint8_t byte_array_t::checksum() const
{
    uint8_t sum = 0;

    for ( std::size_t i = 0, s = m_vec.size(); i < s; ++i )
    {
        sum += m_vec[i];
    }

    //return static_cast<uint8_t>( ( ( ~sum ) + 1 ) & 0xFF );
    return sum;
}
