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

#include "utils.h"

#include "aes.h"
#include "modes.h"

#pragma comment ( lib, "cryptlib.lib" )

const int AES_BLOCK_SIZE = 16;

void rfid_aes_encrypt(
    uint8_t *to_buf,
    const uint8_t *from_buf,
    const size_t len,
    const uint8_t *key,
    const size_t key_len )
{
    if ( len % AES_BLOCK_SIZE != 0 ) return;
    CryptoPP::ECB_Mode< CryptoPP::AES >::Encryption encryptor( key, key_len );
    encryptor.ProcessData( to_buf, from_buf, len );
}

void rfid_aes_decrypt(
    uint8_t *to_buf,
    const uint8_t *from_buf,
    const size_t len,
    const uint8_t *key,
    const size_t key_len )
{
    if ( len % AES_BLOCK_SIZE != 0 ) return;
    CryptoPP::ECB_Mode< CryptoPP::AES >::Decryption decryptor( key, key_len );
    decryptor.ProcessData( to_buf, from_buf, len );
}
