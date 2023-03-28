#pragma once
#include "EbmlNumericElements.h"
#include "EbmlMasterElement.h"
#include "EbmlStringElement.h"
#include "EbmlBinaryElement.h"
#include "EbmlFixedBinaryElement.h"
#include <type_traits>

/*
using std::underlying_type_t;
#define DEFINE_ENUM_OPERATOR(enum, op)                                                                                                                                              \
    inline constexpr enum operator op (const enum a, const enum b){ return static_cast<enum>(static_cast<underlying_type_t<enum>>(a) op static_cast<underlying_type_t<enum>>(b)); } \
    inline constexpr enum operator op##=(enum& a, const enum b) { a = a op b; return a; }

#define DEFINE_ENUM_OPERATORS(enum) \
    DEFINE_ENUM_OPERATOR(enum, |)   \
    DEFINE_ENUM_OPERATOR(enum, &)   \
    DEFINE_ENUM_OPERATOR(enum, ^)   \
    inline constexpr enum operator ~ (const enum a) { return static_cast<enum>(~static_cast<underlying_type_t<enum>>(a)); } \
    inline constexpr operator bool(const enum a) { return static_cast<underlying_type_t<enum>>(a) == 0; }
*/

/*
template <auto _val>
struct Constant { static constinit inline auto value = _val; };

template <typename> inline constexpr bool is_constant_v = false;
template <auto val> inline constexpr bool is_constant_v<Constant<val>> = true;

template <typename T> concept WrappedConstant = is_constant_v<T>;
*/

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

class SomeMasterElement;

using SomeElement = BasicEbmlElement<0x4255, SomeMasterElement, EbmlUIntElement>;
using SomeOtherElement = BasicEbmlElement<0x4257, SomeMasterElement, EbmlFixedBinaryElement, 123>;
//using YetAnotherElement = BasicEbmlElement<0x4257, SomeMasterElement, EbmlFixedBinaryElement, 123>;


class SomeMasterElement final : public EbmlMasterElement<2>
{
public:
    static inline constinit EbmlElementIDType id = 123;

public:
    SomeMasterElement(EbmlElementBasePtr parent) : EbmlMasterElement(parent) {}

public:
    struct Child { enum TYPE: uint64_t
    {
        NONE             = 0ull,
        SomeElement      = 1ull << 0,
        SomeOtherElement = 1ull << 1
    };};
    
public:
    void load_elements(Child::TYPE children_to_load, Child::TYPE stop_at = Child::NONE)
    {
        // Keep iterating until we reach the end or until we loaded the requested elements
        for (auto child_iter = get_iterator(); child_iter && children_to_load; ++child_iter)
        {
            const auto current_child_id = child_iter.get_current_child_id();
            // Element that can appear at-most once
            if (current_child_id == SomeElement::id)
            {
                if (children_to_load & Child::SomeElement)
                {
                    some_element = shared_ptr<SomeElement>(new SomeElement(shared_from_this()));

                    // Clear the flag to stop searching for this element
                    children_to_load = (Child::TYPE)(children_to_load ^ Child::SomeElement);
                }
                else if (stop_at & Child::SomeElement)
                    break;
            }
            else if (current_child_id == SomeOtherElement::id)
            {
                if (children_to_load & Child::SomeOtherElement)
                {
                    some_other_element_elements.emplace_back(new SomeOtherElement(shared_from_this()));
                    // Don't clear the flag because more elements like it may still appear
                }
                else if (stop_at & Child::SomeOtherElement)
                    break;
            }
        }
    }

public:
    shared_ptr<SomeElement> some_element;
    vector<shared_ptr<SomeOtherElement>> some_other_element_elements;
};