#pragma once
#include "Common.h"
#include "EbmlElementID.h"
#include "EbmlElementLength.h"
#include "MatroskaElementSpecification.h"

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
    EbmlElement(std::iostream& stream);

    /******************************************************************************************************/
    /********************************************** Getters ***********************************************/
    /******************************************************************************************************/
    EbmlElementID get_id() const { return m_id; }
    EbmlElementLength get_length() const { return m_length; }

public:
    /******************************************************************************************************/
    /******************************************* Iterator Stuff *******************************************/
    /******************************************************************************************************/
    struct Iterator
    {
        Iterator(EbmlElement& parent);

        std::shared_ptr<EbmlElement> operator*();
        Iterator& operator++();

        friend bool operator!=(const Iterator& current, uint64_t end_offset);

    private:
        EbmlElement& m_parent;
        std::shared_ptr<EbmlElement> m_current_element;
    };

    Iterator begin() { return Iterator(*this); }
    constexpr uint64_t end() { return _get_offset(EbmlOffset::End); }

private:
    EbmlElement(std::shared_ptr<EbmlElement> parent);

    /******************************************************************************************************/
    /****************************************** Internal Utility ******************************************/
    /******************************************************************************************************/
    constexpr uint64_t _get_offset(EbmlOffset seek_pos) const;
    inline void _seek_to(EbmlOffset seek_pos) const;
    inline void _seek_to(uint64_t seek_pos) const;

private:
    std::iostream& m_stream;
    uint64_t m_offset;
    EbmlElementID m_id;
    EbmlElementLength m_length;
    std::shared_ptr<EbmlElement> m_parent;
};
