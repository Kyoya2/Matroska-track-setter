#pragma once
#include "Common.h"
#include "EbmlElementID.h"
#include "EbmlElementLength.h"
#include "MatroskaElementSpecification.h"

enum class EbmlSeekPosition
{
    Header,
    Data,
    End
};

class EbmlElement
{
    EbmlElement(std::iostream& stream, EbmlElement* parent);

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
        // start_pos is the offset to the data of the current element
        Iterator(const std::iostream& stream, uint64_t start_pos);

        EbmlElement operator*() const;
        Iterator& operator++();

        friend bool operator!=(const Iterator& current, uint64_t end_offset);

    private:
        const std::iostream& m_stream;

        // store stream pos to avoid calling 'tellg' twice (once in 'EbmlElement' Ctor [unavoidable] and once in 'operator==' [avoided])
        uint64_t m_stream_pos;
    };

    Iterator begin() { return Iterator(m_stream, _get_offset(EbmlSeekPosition::Data)); }
    uint64_t end() { return _get_offset(EbmlSeekPosition::End); }

private:
    /******************************************************************************************************/
    /****************************************** Internal Utility ******************************************/
    /******************************************************************************************************/
    constexpr uint64_t _get_offset(const EbmlSeekPosition seek_pos) const;
    inline void _seek_to(const EbmlSeekPosition seek_pos) const;

private:
    std::iostream& m_stream;
    uint64_t m_offset;
    EbmlElementID m_id;
    EbmlElementLength m_length;
    EbmlElement* m_parent;
};
