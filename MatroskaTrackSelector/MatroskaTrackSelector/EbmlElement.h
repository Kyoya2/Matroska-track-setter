#pragma once
#include <utility>
#include <unordered_map>

#include "Common.h"
#include "EbmlElementID.h"
#include "EbmlElementLength.h"
#include "MatroskaElementSpecification.h"
#include "BasicSharedPtr.h"
#include "ElementIterator.h"

using std::unordered_map;

class ElementIterator;

// Offsets relative to the current element
enum class EbmlOffset
{
    Header, // Offset to the first character of the EBML ID
    Data,   // Offset to the first character if the data (after EBML ID and Length)
    End     // Offset to the first character after the end of the data
};

class EbmlElement
{
public:
    static BasicSharedPtr<EbmlElement> s_construct_from_stream(std::iostream& stream);

    /******************************************************************************************************/
    /********************************************** Getters ***********************************************/
    /******************************************************************************************************/
    EbmlElementID get_id() const { return m_id; }
    EbmlElementLength get_length() const { return m_length; }

public:
    /******************************************************************************************************/
    /******************************************* Iterator Stuff *******************************************/
    /******************************************************************************************************/
    ElementIterator begin();
    constexpr void* end() { return nullptr; }

public:
    /******************************************************************************************************/
    /*************************************** Functions for iteration **************************************/
    /******************************************************************************************************/
    BasicSharedPtr<EbmlElement> get_next_element();
    BasicSharedPtr<EbmlElement> get_first_child();

    bool is_last() { return this->_get_offset(EbmlOffset::End) == m_parent->_get_offset(EbmlOffset::End); }

    void find_children(unordered_map<EbmlElementIDType, BasicSharedPtr<EbmlElement>>& children);

   /******************************************************************************************************/
   /********************************************* Data getters *******************************************/
   /******************************************************************************************************/
    Buffer binary_value() const;
    uint64_t uint_value() const;
    int64_t int_value() const;

private:
    /******************************************************************************************************/
    /**************************************** Internal Constructors ***************************************/
    /******************************************************************************************************/
    EbmlElement(BasicSharedPtr<EbmlElement> parent);
    EbmlElement(std::iostream& stream);

    /******************************************************************************************************/
    /****************************************** Internal Utility ******************************************/
    /******************************************************************************************************/
    static BasicSharedPtr<EbmlElement> _s_construct_from_parent(BasicSharedPtr<EbmlElement>& parent);
    constexpr uint64_t _get_offset(EbmlOffset seek_pos) const;
    inline void _seek_to(EbmlOffset seek_pos) const;
    inline void _seek_to(uint64_t seek_pos) const;
    void _initialize_as_root();

    template <typename... Args>
    static BasicSharedPtr<EbmlElement> s_get(Args&&... args);


    // Reads the raw content of the elemnt into the given container
    void _read_content(void* container) const;

private:
    std::iostream& m_stream;
    uint64_t m_offset;
    EbmlElementID m_id;
    EbmlElementLength m_length;
    BasicSharedPtr<EbmlElement> m_parent;   // Owned
    BasicSharedPtr<EbmlElement> m_self;     // Not owned

public:
    friend class BasicSharedPtr<EbmlElement>;
};

template<typename ...Args>
inline BasicSharedPtr<EbmlElement> EbmlElement::s_get(Args&& ...args)
{
    BasicSharedPtr<EbmlElement> element = BasicSharedPtr<EbmlElement>::make_basic_shared(std::forward<Args>(args)...);
    element->m_self = element;
    element->m_self.release_ownership();
    return element;
}
