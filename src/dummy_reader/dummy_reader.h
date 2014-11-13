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

#ifndef __EZ_RFID_DUMMY_READER_H__
#define __EZ_RFID_DUMMY_READER_H__

/**
 * @brief dummy RFID reader class
 * 
 * @note a dummy tag represents a single file on disk with pre-defined file structure, 
 *       which contains bytes of tid/epc/user zone seperately. Tags are distinguished  
 *       by string-based unique ID, which is generated at the time tag created.
 */
class dummy_reader {
public:
  /**
   * @brief create a new dummy tag
   * 
   * @note by default tid/epc/user zones are of unlimited size
   * @return the unique ID of the newly created tag
   */
  const char* create_tag();
  /**
   * @brief remove existing dummy tag by ID
   * 
   * @note remove operation shall fail if id doesn't point to an existing tag
   * @param id string-baseed unique ID of tag
   */
  void remove_tag(const char* id);
  /**
   * @brief remove all tags
   */
  void remove_all_tags();
  /**
   * @brief read bytes from tag with options
   * 
   * @param bank could be tid
   */
  void read(const int bank, const size_t offset, const size_t words, std::vector<byte_array_t>& datas, const char* password = NULL);
  void write(const int bank, const size_t offset, const size_t words, const char* data, const char* password = NULL);
};

#endif // __EZ_RFID_DUMMY_READER_H__
