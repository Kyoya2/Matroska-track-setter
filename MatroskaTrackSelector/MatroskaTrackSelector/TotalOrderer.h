#pragma once
#include <set>
#include <algorithm>

#include "Common.h"

enum class Order
{
    Bigger,     // LHS is bigger
    Smaller,    // LHS is smaller
    Unknown     // The order can't be determined because of insufficient info
};

template <typename T>
class TotalOrderer
{
public:
    TotalOrderer() = default;

public:
    void register_element(T element);

    // 'element' must already be registered by one of the "register_XXX" functions
    void register_bigger_element(T element, T bigger_element);
    void register_smaller_element(T element, T smaller_element);

    Order get_order(T lhs, T rhs);

PRIVATE:
    struct OrderDescriptor
    {
        OrderDescriptor(T element) : element(element) {}

        T element;
        std::set<T> smaller_elements;
        std::set<T> bigger_elements;
    };

private:
    vector<OrderDescriptor> m_order_descriptors;
};

template<typename T>
inline void TotalOrderer<T>::register_element(T element)
{
    m_order_descriptors.emplace_back(element);
}

template<typename T>
inline void TotalOrderer<T>::register_bigger_element(T element, T bigger_element)
{
    // Look for an order descriptor of both elements
    OrderDescriptor* element_order_descriptor = nullptr;
    OrderDescriptor* bigger_element_descriptor = nullptr;
    for (const OrderDescriptor& order_descriptor : m_order_descriptors)
    {
        if (order_descriptor.element == element)
        {
            element_order_descriptor = &order_descriptor;
        }
        else if (order_descriptor.element == bigger_element)
        {
            bigger_element_descriptor = &order_descriptor;
        }

        if (element_order_descriptor && bigger_element_descriptor)
            break;
    }

    // Register "element" if a descriptor wasn't found
    if (nullptr == element_order_descriptor)
    {
        register_element(bigger_element);
        element_order_descriptor = &m_order_descriptors.back();
    }

    // Set "bigger_element" to be bigger then "element"
    element_order_descriptor->bigger_elements.emplace(bigger_element);

    ////???????
}

template<typename T>
inline void TotalOrderer<T>::register_smaller_element(T element, T smaller_element)
{
}

template<typename T>
inline Order TotalOrderer<T>::get_order(T lhs, T rhs)
{
    return Order();
}
