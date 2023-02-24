/*   
 *   Matroska track setter  Copyright (C) 2022  Kyoya2
 *   
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *   
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *   
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once
#include <utility>
#include <unordered_map>

#include "Common.h"
#include "EbmlElementID.h"
#include "EbmlElementLength.h"
#include "MatroskaElementSpecification.auto.h"
#include "BasicSharedPtr.h"

using std::unordered_map;

// Offsets relative to the current element
enum class EbmlOffset
{
    Header, // Offset to the first character of the EBML ID
    Data,   // Offset to the first character if the data (after EBML ID and Length)
    End     // Offset to the first character after the end of the data
};

class EbmlElement;

// Typedefs
using EbmlElementPtr = BasicSharedPtr<EbmlElement>;
using EbmlElements = vector<EbmlElementPtr>;

class EbmlElement
{
public:
    static EbmlElementPtr s_construct_from_stream(std::iostream& stream);

    /******************************************************************************************************/
    /********************************************** Getters ***********************************************/
    /******************************************************************************************************/
    inline EbmlElementID get_id() const { return m_id; }
    inline EbmlElementLength get_data_length() const { return m_length; }
    inline uint64_t get_offset() const { return m_offset; }
    inline size_t get_total_size() const { return m_id.get_encoded_size() + m_length.get_encoded_size() + m_length.get_value(); }

public:
    /******************************************************************************************************/
    /*************************************** Functions for iteration **************************************/
    /******************************************************************************************************/
    // This function WILL overwrite the current element if it's refcout is 1.
    // Make sure to take ownership of the pointer if you don't want it to be overwritten.
    EbmlElementPtr get_next_element();
    EbmlElementPtr get_first_child();
    inline EbmlElementPtr get_parent() { return m_parent; }

    bool is_last() { return this->_get_offset(EbmlOffset::End) == m_parent->_get_offset(EbmlOffset::End); }

    // Returns the first child element with the given ID or null if a child with that ID wasn't found
    EbmlElementPtr find_child(const EbmlElementIDType id);

    // Returns a vector with all children of the current element with the given ID
    EbmlElements get_identical_children_by_id(const EbmlElementIDType id);

    // Sets the value of each {ID:Element} pair to a child of the current element with the corresponding key-ID.
    // All requested children should be unique elements (ones that can't appear more then once in one parent).
    void get_unique_children(unordered_map<EbmlElementIDType, EbmlElementPtr>& children);

   /******************************************************************************************************/
   /********************************************* Data getters *******************************************/
   /******************************************************************************************************/
    Buffer get_binary_value();
    uint64_t get_uint_value();
    int64_t get_int_value();
    string get_string_value();
    bool get_bool_value();

   /******************************************************************************************************/
   /****************************************** Element modifiers *****************************************/
   /******************************************************************************************************/
    void update_bool_value(bool new_value);
    void update_uint_value(uint64_t new_value);
    void overwrite_with_bool_element(EbmlElementIDType new_element_id, bool value);

   /******************************************************************************************************/
   /******************************************** Miscellaneous *******************************************/
   /******************************************************************************************************/
    // Calculate distance of current elementy from another element
    // Both elements must be on the same level
    uint64_t get_distance_from(EbmlElementPtr other);

    // Moves the current element to a given parent.
    // Note that after calling this function. elements_to_adjust must contain all referenced elements
    // between the new parent and the current element (not including the new parent, current element or current parent)
    // Returns the amount by which all relevant elements were shifted
    int32_t move_to(EbmlElementPtr new_parent, EbmlElements& elements_to_adjust);

PRIVATE:
    /******************************************************************************************************/
    /**************************************** Internal Constructors ***************************************/
    /******************************************************************************************************/
    explicit EbmlElement(EbmlElementPtr parent);
    explicit EbmlElement(std::iostream& stream);

    /******************************************************************************************************/
    /****************************************** Internal Utility ******************************************/
    /******************************************************************************************************/
    static EbmlElementPtr _s_construct_from_parent(EbmlElementPtr& parent);
    constexpr uint64_t _get_offset(EbmlOffset seek_pos) const;
    inline void _seek_to(EbmlOffset seek_pos) const;
    inline void _seek_to(uint64_t seek_pos) const;
    void _initialize_as_root();
    void _create_void_element(size_t size); // Creates a void element of the given size at the current stream position

    // This function creates a pointer of an ebml element using any available contructor
    template <typename... Args>
    static EbmlElementPtr s_get(Args&&... args);

    // Reads the raw content of the elemnt into the given container
    void _read_content(void* container) const;

PRIVATE:
    std::iostream& m_stream;
    uint64_t m_offset;
    EbmlElementID m_id;
    EbmlElementLength m_length;
    EbmlElementPtr m_parent;   // Owned
    EbmlElementPtr m_self;     // Not owned

public:
    friend class BasicSharedPtr<EbmlElement>;
};

template<typename ...Args>
inline EbmlElementPtr EbmlElement::s_get(Args&& ...args)
{
    EbmlElementPtr element = EbmlElementPtr::make_basic_shared(std::forward<Args>(args)...);
    element->m_self = element;
    element->m_self.release_ownership();
    return element;
}

inline void EbmlElement::_seek_to(const EbmlOffset seek_pos) const
{
    _seek_to(_get_offset(seek_pos));
}

inline void EbmlElement::_seek_to(uint64_t seek_pos) const
{
    m_stream.seekp(seek_pos);
}