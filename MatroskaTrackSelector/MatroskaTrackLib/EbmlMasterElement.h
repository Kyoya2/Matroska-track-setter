#pragma once
#include "EbmlElement.h"
#include "EbmlElementIterator.h"

template <uint8_t id_size>
class EbmlMasterElement : public EbmlElement<id_size>
{
protected:
    using EbmlElement<id_size>::EbmlElement;

protected:
    EbmlElementIterator get_iterator() const;
};

template <uint8_t id_size>
EbmlElementIterator EbmlMasterElement<id_size>::get_iterator() const
{
    return EbmlElementIterator(
        EbmlElementBase::_get_stream(),
        EbmlElementBase::_get_offset(EbmlOffset::Data),
        EbmlElementBase::_get_offset(EbmlOffset::End));
}
