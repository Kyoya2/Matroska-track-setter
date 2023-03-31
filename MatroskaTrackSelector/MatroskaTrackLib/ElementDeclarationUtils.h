#pragma once
#include "EbmlNumericElements.h"
#include "EbmlMasterElement.h"
#include "EbmlStringElement.h"
#include "EbmlBinaryElement.h"
#include "EbmlFixedBinaryElement.h"
#include <type_traits>

// A template for declaring non-master EBML elements
#define CurrentTPrimitiveClass TPrimitive<Utility::get_byte_size(ElementID), TPrimitiveParams...>
template <EbmlElementIDType ElementID, typename TParentElement, template<uint8_t, auto...> typename TPrimitive, auto... TPrimitiveParams>
class BasicEbmlElement final : CurrentTPrimitiveClass
{
    // We want to verify that `TPrimitive` is derived from a specialization of `EbmlPrimitiveElement` but IDK how to do that.
    // Instead, I check that `TPrimitive` is derived from an `EbmlElement` that is not a master element
    static_assert(
        std::derived_from<CurrentTPrimitiveClass, EbmlElementBase> &&
        !std::derived_from<CurrentTPrimitiveClass, EbmlMasterElement<Utility::get_byte_size(ElementID)>>
        );

    // Make sure that `TParent` is a master element
    //static_assert(std::derived_from<TParentElement, EbmlMasterElement>);

    using CurrentTPrimitiveClass::TPrimitive;
    static constinit inline EbmlElementIDType id = ElementID;

    friend TParentElement;
};
#undef CurrentTPrimitiveClass