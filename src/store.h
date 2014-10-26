//RFID Relevant Application Development Kit
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

#ifndef __EZ_RFID_STORE_H__
#define __EZ_RFID_STORE_H__

#include "byte_array.h"

#include <string>
#include <iostream>

class storable;
class archive
{
public:
    virtual ~archive() {}

    virtual void write( const uint8_t* ba, uint32_t size ) = 0;
    virtual void read( uint8_t* ba, uint32_t size ) = 0;

#define ARCHIVE_WRITE_REF(valref) write((const uint8_t*)&valref,sizeof(valref))
    void write( uint32_t v )
    {
        ARCHIVE_WRITE_REF( v );
    }

#define ARCHIVE_EREAD_REF(valref) read((uint8_t*)&valref,sizeof(valref))
    void read( uint32_t& v )
    {
        ARCHIVE_EREAD_REF( v );
    }

#define ARCHIVE_READ(val) \
    read(val); return *this;
    archive& operator >>( uint32_t &obj )
    {
        ARCHIVE_READ( obj );
    }

#define ARCHIVE_WRITE(val) \
    write(val); return *this;
    archive& operator <<( const uint32_t &obj )
    {
        ARCHIVE_WRITE( obj );
    }

    archive& operator >>( std::string &obj );
    archive& operator <<( std::string obj );
};

class storable
{
public:
    virtual ~storable() {}

    virtual bool save( archive &ar ) = 0;
    virtual bool load( archive &ar ) = 0;
};

class archive_impl: public archive
{
public:
    archive_impl( std::istream *stream );
    archive_impl( std::ostream *stream );
    virtual void write( const uint8_t *buf, uint32_t size );
    virtual void read( uint8_t *buf, uint32_t size );

protected:
    std::istream* in_;
    std::ostream* out_;
};

#endif // __EZ_RFID_STORE_H__
