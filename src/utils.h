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

#ifndef __EZ_RFID_UTILS_H__
#define __EZ_RFID_UTILS_H__

#include "define.h"

const int DEFAULT_AES_KEY_SIZE = 16;

/**
 * @brief rfid_aes_encrypt
 * @param to_buf
 * @param from_buf
 * @param len
 * @param key
 * @param key_len
 */
extern void rfid_aes_encrypt(
    uint8_t *to_buf,
    const uint8_t *from_buf,
    const size_t len,
    const uint8_t *key,
    const size_t key_len = DEFAULT_AES_KEY_SIZE
);

/**
 * @brief rfid_aes_decrypt
 * @param to_buf
 * @param from_buf
 * @param len
 * @param key
 * @param key_len
 */
extern void rfid_aes_decrypt(
    uint8_t *to_buf,
    const uint8_t *from_buf,
    const size_t len,
    const uint8_t *key,
    const size_t key_len = DEFAULT_AES_KEY_SIZE
);

#endif // __EZ_RFID_UTILS_H__
