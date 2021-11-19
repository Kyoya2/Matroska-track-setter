#pragma once

// The following 5 macros are a utility for removing parentheses on macro expansion
#define REMOVE_PARENTHESES(X) ESC(ISH X)
#define ISH(...) ISH __VA_ARGS__
#define ESC(...) ESC_(__VA_ARGS__)
#define ESC_(...) VAN ## __VA_ARGS__
#define VANISH

#define GET_ID(element_name) element_name##_ID
#define GET_TYPE(element_name) element_name##_TYPE
#define blaaaa(child_name) REMOVE_PARENTHESES(child_name##_TYPE)
#define GET_CHILD_VALUE(children_map, child_name) (children_map[GET_ID(child_name)]->REMOVE_PARENTHESES(GET_TYPE(child_name))##_value())

// Element specification
{ELEMENTS_INFO}


{ENUM_ELEMENTS}