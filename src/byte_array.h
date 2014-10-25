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

#ifndef __EZ_RFID_BYTE_ARRAY_H__
#define __EZ_RFID_BYTE_ARRAY_H__

#include "define.h"

#include <string>
#include <vector>
#include <assert.h>

/**
 * @brief byte array struct provides convenient byte operation
 */
class byte_array_t
{
public:
    // constructors and de-constructors
    /**
     * @brief default empty constructor
     */
    byte_array_t()
    {
    }
    /**
     * @brief construct from char array
     * @param data head pointer of char array
     * @param len size of char array
     */
    byte_array_t( const char* data, const std::size_t len ) :
        m_vec( data, data + len )
    {
    }
    /**
     * @brief copy constructor
     * @param array another array to copy from
     */
    byte_array_t( const byte_array_t& array ) :
        m_vec( array.m_vec )
    {
    }
    /**
     * @brief construct from hex string
     * @note different with constructor from char array on that the string is in hex format
     * e.g. "313233" equals to "123" in char array format
     * @param hex hex string to construct from
     */
    byte_array_t( const std::string hex );
    /**
     * @brief de-constructor
     */
    ~byte_array_t()
    {
        clear();
    }

    // basic array operations
    /**
     * @brief make empty byte array object
     */
    void clear()
    {
        m_vec.clear();
    }
    /**
     * @brief check whether byte array is empty
     * @return true if empty, otherwise false
     */
    bool empty() const
    {
        return m_vec.empty();
    }
    /**
     * @brief gets const header pointer of char contents
     * @note based on the fact that std::vector is implemented base on a continuous allocated memory
     * @return const head pointer of array content as char array
     */
    const char* data() const
    {
        return &m_vec[0];
    }
    /**
     * @brief get array size
     * @return array size
     */
    std::size_t size() const
    {
        return m_vec.size();
    }
    /**
     * @brief size in words
     * @note a byte array with size of 3, calls word_size() returns 2
     */
    std::size_t word_size() const;
    /**
     * @brief size in dwords
     * @note a byte array with size of 3, calls dword_size() returns 1
     */
    std::size_t dword_size() const;
    /**
     * @brief a to-hex-string implementation
     * @note e.g. byte array ("123"), as_hex_string() returns "313233"
     * @return hex format of byte array content
     */
    std::string as_hex_string() const;
    /**
     * @brief operator [] supports navigation
     * @param i index of char to fetch in byte array
     * @return char at index 'i'
     */
    const char operator[]( const std::size_t i ) const
    {
        return m_vec[i];
    }
    /**
     * @brief at method supports navigation
     * @param i index of char to fetch in byte array
     * @return char at index 'i'
     */
    const char at( const std::size_t i ) const
    {
        return m_vec.at( i );
    }
    /**
     * @brief get sub array
     * @param start start index
     * @param len length to extract
     * @note if start adds len exceeds array size, contents after start will be extracted;
     * if start is bigger than size, empty array returned
     * @return extracted sub array
     */
    byte_array_t sub_array( const std::size_t start,
                            const std::size_t len ) const
    {
        std::size_t s = size();
        if ( start >= s || !len )
            return byte_array_t();
        else
            return byte_array_t( data() + start, ( ( start + len ) <= s ? len : s - start ) );
    }

    // array appenders
    /**
     * @brief appends another byte array
     */
    byte_array_t& append( const byte_array_t& data )
    {
        m_vec.insert( m_vec.end(), data.m_vec.begin(), data.m_vec.end() );
        return *this;
    }
    /**
     * @brief appends char array
     */
    byte_array_t& append( const char* data, const std::size_t len )
    {
        std::copy( data, data + len, std::back_inserter( m_vec ) );
        return *this;
    }
    /**
     * @brief append a single byte
     */
    byte_array_t& append( const char& val )
    {
        m_vec.push_back( val );
        return *this;
    }

    // checksum functions
    /**
     * @brief gets check sum in 8-bit integer
     */
    uint8_t checksum() const;
    /**
     * @brief gets CRC in 16-bits integer
     */
    uint16_t crc16() const;

private:
    std::vector<char> m_vec;
};

#endif // __EZ_RFID_BYTE_ARRAY_H
