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

class byte_array_t
{
public:
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
  const char* data() const
  {
    return &m_vec[0];
  }
  std::size_t size() const
  {
    return m_vec.size();
  }
  std::string as_string() const;
  const char operator[]( const std::size_t i ) const
  {
    return m_vec[i];
  }
  std::size_t word_size() const;
  std::size_t dword_size() const;
  byte_array_t& append( const byte_array_t& data )
  {
    m_vec.insert( m_vec.end(), data.m_vec.begin(), data.m_vec.end() );
    return *this;
  }
  byte_array_t& append( const uint16_t val );
  byte_array_t& append( const uint8_t val )
  {
    m_vec.push_back( val );
    return *this;
  }
  byte_array_t& append( const char* data, const std::size_t len );
  byte_array_t& append( const char* data, const std::size_t offset,
                        const std::size_t len );
  byte_array_t& append( const byte_array_t& data, const std::size_t offset,
                        const std::size_t len );
  uint8_t checksum() const;
  uint16_t crc16() const;
  void swap( byte_array_t& vec )
  {
    m_vec.swap( vec.m_vec );
  }
  byte_array_t sub_array( const std::size_t start,
                          const std::size_t len ) const
  {
    assert( start + len <= size() );
    return byte_array_t( data() + start, len );
  }
  char at( const std::size_t index ) const
  {
    return m_vec.at( index );
  }

private:
  std::vector<char> m_vec;
};

#endif // __EZ_RFID_BYTE_ARRAY_H
