"""
    Matroska track setter  Copyright (C) 2023  Kyoya2

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
"""


def simple_format(string: str, **kwargs) -> str:
    for key, val in kwargs.items():
        string = string.replace('{' + key + '}', str(val))
    return string


PRIMITIVE_ELEMENT_FORMAT = r'using {name} = BasicEbmlElement<{type_class_name}, {parent_name}, {id}>;'

# A generic template for both the root and non-root master elements
MASTER_ELEMENT_FORMAT = \
    r"""class {name} final : public EbmlMasterElement<{id_size_in_bytes}>
    {
    public:
        static inline constinit EbmlElementIDType id = {id};
    
    public:
        {name}{constructor_impl}
    
    public:
        struct Child { enum TYPE: uint64_t
        {
            NONE = 0ull,
            {children_enum_values}
        };};
    
    public:
        void load_elements(Child::TYPE children_to_load, Child::TYPE stop_at = Child::NONE)
        {
            // Keep iterating until we reach the end or until we loaded the requested elements
            for (auto child_iter = get_iterator(); child_iter && children_to_load; ++child_iter)
            {
                const auto current_child_id = child_iter.get_current_child_id();
                {child_loading_logic}
            }
        }
    
    public:
        {children_members}
    {parent_friend}};"""


class RootElementFormats:
    ConstructorImpl = '(std::iostream& stream) : EbmlMasterElement(stream) {TODO}'
    ParentFriend = ''

class NonRootMasterElementFormats:
    ConstructorImpl = '(EbmlElementPtr parent) : EbmlMasterElement(parent) {}'
    ParentFriend = 'private:\n    friend class {parent_name};'

ROOT_ELEMENT_FORMAT = simple_format(
    MASTER_ELEMENT_FORMAT,
    constructor_impl = RootElementFormats.ConstructorImpl,
    parent_friend    = RootElementFormats.ParentFriend
)

NON_ROOT_MASTER_ELEMENT_FORMAT = simple_format(
    MASTER_ELEMENT_FORMAT,
    constructor_impl = NonRootMasterElementFormats.ConstructorImpl,
    parent_friend    = NonRootMasterElementFormats.ParentFriend
)

UNIQUE_ELEMENT_MEMBER_FORMAT = "    shared_ptr<{name}> {member_name};"
UNIQUE_ELEMENT_LOADING_LOGIC = \
         """if (current_child_id == {name}::id)
            {
                if (children_to_load & Child::{name})
                {
                    {member_name} = shared_ptr<{name}>(new {name}(shared_from_this()));

                    // Clear the flag to stop searching for this element
                    children_to_load = (Child::TYPE)(children_to_load ^ Child::{name});
                }
                else if (stop_at & Child::{name})
                    break;
            }"""


NON_UNIQUE_ELEMENT_MEMBER_FORMAT = "    vector<shared_ptr<{name}>> {member_name}_elements;"
NON_UNIQUE_ELEMENT_LOADING_LOGIC = \
         """if (current_child_id == {name}::id)
            {
                if (children_to_load & Child::{name})
                {
                    {member_name}.emplace_back(new {name}(shared_from_this()));
                }
                else if (stop_at & Child::{name})
                    break;
            }"""