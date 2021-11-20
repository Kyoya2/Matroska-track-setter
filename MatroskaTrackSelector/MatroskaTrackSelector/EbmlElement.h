#pragma once
#include <utility>
#include <unordered_map>

#include "Common.h"
#include "EbmlElementID.h"
#include "EbmlElementLength.h"
#include "MatroskaElementSpecification.h"
#include "BasicSharedPtr.h"

using std::unordered_map;

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
    /*************************************** Functions for iteration **************************************/
    /******************************************************************************************************/
    BasicSharedPtr<EbmlElement> get_next_element();
    BasicSharedPtr<EbmlElement> get_first_child();

    bool is_last() { return this->_get_offset(EbmlOffset::End) == m_parent->_get_offset(EbmlOffset::End); }

    // Returns the first child element with the given ID or null if a child with that ID wasn't found
    BasicSharedPtr<EbmlElement> find_child(const EbmlElementIDType id);

    // Returns a vector with all children of the current element with the given ID
    vector<BasicSharedPtr<EbmlElement>> get_identical_children_by_id(const EbmlElementIDType id);

    // Sets the value of each {ID:Element} pair to a child of the current element with the corresponding key-ID.
    // All requested children should be unique elements (ones that can't appear more then once in one parent).
    void get_unique_children(unordered_map<EbmlElementIDType, BasicSharedPtr<EbmlElement>>& children);

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
    EbmlElement& operator=(const EbmlElement& other) = default;
    EbmlElement& operator=(EbmlElement&& other)
    {
        m_stream = std::move(other.m_stream);
        m_offset = std::move(other.m_offset);
        m_id = std::move(other.m_id);
        m_length = std::move(other.m_length);
        m_parent = std::move(other.m_parent);
        m_self = std::move(other.m_self);
        return *this;
    }

    /******************************************************************************************************/
    /****************************************** Internal Utility ******************************************/
    /******************************************************************************************************/
    static BasicSharedPtr<EbmlElement> _s_construct_from_parent(BasicSharedPtr<EbmlElement>& parent);
    constexpr uint64_t _get_offset(EbmlOffset seek_pos) const;
    inline void _seek_to(EbmlOffset seek_pos) const;
    inline void _seek_to(uint64_t seek_pos) const;
    void _initialize_as_root();
    void _reconstruct_from_parent(BasicSharedPtr<EbmlElement>& parent);

    template <typename... Args>
    static BasicSharedPtr<EbmlElement> s_get(Args&&... args);

    // Reads the raw content of the elemnt into the given container
    void _read_content(void* container) const;

private:
    reference_wrapper<std::iostream> m_stream;
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
