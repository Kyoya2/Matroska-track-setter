#pragma once
#include <utility>
#include <unordered_map>

#include "Common.h"
#include "EbmlElementID.h"
#include "EbmlElementLength.h"
#include "MatroskaElementSpecification.h"
#include "BasicSharedPtr.h"

DECL_EXCEPTION(UnsupportedDocument);
DECL_EXCEPTION(UnexpectedElementException);
DECL_EXCEPTION(NoMoreElements);
DECL_EXCEPTION(UnexpectedValueException);
DECL_EXCEPTION(ElementTooSmall);
DECL_EXCEPTION(SizeTooSmall);

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
    Buffer get_binary_value() const;
    uint64_t get_uint_value() const;
    int64_t get_int_value() const;
    string get_string_value() const;
    bool get_bool_value() const;

   /******************************************************************************************************/
   /****************************************** Element modifiers *****************************************/
   /******************************************************************************************************/
    void change_bool_value(bool new_value);
    void overwrite_with_bool_element(EbmlElementIDType new_element_id, bool value);

PRIVATE:
    /******************************************************************************************************/
    /**************************************** Internal Constructors ***************************************/
    /******************************************************************************************************/
    explicit EbmlElement(BasicSharedPtr<EbmlElement> parent);
    explicit EbmlElement(std::iostream& stream);

    /******************************************************************************************************/
    /****************************************** Internal Utility ******************************************/
    /******************************************************************************************************/
    static BasicSharedPtr<EbmlElement> _s_construct_from_parent(BasicSharedPtr<EbmlElement>& parent);
    constexpr uint64_t _get_offset(EbmlOffset seek_pos) const;
    inline void _seek_to(EbmlOffset seek_pos) const;
    inline void _seek_to(uint64_t seek_pos) const;
    void _initialize_as_root();
    void _create_void_element(size_t size); // Creates a void element of the given size at the current stream position

    template <typename... Args>
    static BasicSharedPtr<EbmlElement> s_get(Args&&... args);

    // Reads the raw content of the elemnt into the given container
    void _read_content(void* container) const;

PRIVATE:
    reference_wrapper<std::iostream> m_stream;
    uint64_t m_offset;
    EbmlElementID m_id;
    EbmlElementLength m_length;
    BasicSharedPtr<EbmlElement> m_parent;   // Owned
    BasicSharedPtr<EbmlElement> m_self;     // Not owned

public:
    friend class BasicSharedPtr<EbmlElement>;

    // Debug print
    friend std::ostream& operator<<(std::ostream& stream, const BasicSharedPtr<EbmlElement>& element);
};

template<typename ...Args>
inline BasicSharedPtr<EbmlElement> EbmlElement::s_get(Args&& ...args)
{
    BasicSharedPtr<EbmlElement> element = BasicSharedPtr<EbmlElement>::make_basic_shared(std::forward<Args>(args)...);
    element->m_self = element;
    element->m_self.release_ownership();
    return element;
}
