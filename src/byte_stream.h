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

#include "define.h"
#include "byte_array.h"

#include <sstream>
#include <vector>

class storable;
class basic_byte_stream
{
public:
    virtual void write( const char* data, uint32_t size );
    virtual void read( char* data, uint32_t size );

#define ARCHIVE_WRITE_REF(valref) write((const char*)&valref,sizeof(valref))
    void write( const uint32_t v )
    {
        ARCHIVE_WRITE_REF( v );
    }
    void write( const bool v )
    {
        ARCHIVE_WRITE_REF( v );
    }
    void write( const long long v )
    {
        ARCHIVE_WRITE_REF( v );
    }

#define ARCHIVE_EREAD_REF(valref) read((char*)&valref,sizeof(valref))
    void read( uint32_t& v )
    {
        ARCHIVE_EREAD_REF( v );
    }
    void read( bool& v )
    {
        ARCHIVE_EREAD_REF( v );
    }
    void read( long long& v )
    {
        ARCHIVE_EREAD_REF( v );
    }

#define ARCHIVE_READ(val) \
    read(val); return *this;
    basic_byte_stream& operator >>( uint32_t &obj )
    {
        ARCHIVE_READ( obj );
    }
    basic_byte_stream& operator >>( bool &obj )
    {
        ARCHIVE_READ( obj );
    }
    basic_byte_stream& operator >>( long long &obj )
    {
        ARCHIVE_READ( obj );
    }

#define ARCHIVE_WRITE(val) \
    write(val); return *this;
    basic_byte_stream& operator <<( const uint32_t &obj )
    {
        ARCHIVE_WRITE( obj );
    }
    basic_byte_stream& operator <<( const bool &obj )
    {
        ARCHIVE_WRITE( obj );
    }
    basic_byte_stream& operator <<( const long long &obj )
    {
        ARCHIVE_WRITE( obj );
    }

    basic_byte_stream& operator <<( const std::string& v );
    basic_byte_stream& operator >>( std::string& v );

    basic_byte_stream& operator <<( const storable& v );
    basic_byte_stream& operator >>( storable& v );

    const byte_array_t c_data() const
    {
        std::string str = m_ss.str();
        return byte_array_t( str.c_str(), str.size() );
    }

private:
    std::stringstream m_ss;
};

class storable
{
public:
    virtual ~storable() {}

    virtual void load( basic_byte_stream& bs ) = 0;
    virtual void save( basic_byte_stream& bs ) const = 0;
};
