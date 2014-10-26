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

#include "byte_stream.h"

void basic_byte_stream::write( const char* data, uint32_t size )
{
    m_ss.write( data, size );
}

void basic_byte_stream::read( char* data, uint32_t size )
{
    m_ss.read( data, size );
}

basic_byte_stream& basic_byte_stream::operator <<( const std::string& v )
{
    uint32_t size = v.size();
    *this << size;
    write( v.c_str(), size );
    return *this;
}

basic_byte_stream& basic_byte_stream::operator >>( std::string& v )
{
    uint32_t size;
    *this >> size;
    char* buf = new char[size + 1];
    read( buf, size );
    buf[size] = '\0';
    v = buf;
    delete []buf;
    return *this;
}

basic_byte_stream& basic_byte_stream::operator <<( const storable& v )
{
    v.save( *this );
    return *this;
}

basic_byte_stream& basic_byte_stream::operator >>( storable& v )
{
    v.load( *this );
    return *this;
}
