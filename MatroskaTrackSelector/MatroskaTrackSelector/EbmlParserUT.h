#pragma once
#include "UTCommon.h"
#include "EbmlElement.h"

#include <ios>
#include <fstream>


namespace EbmlParserUT
{
    void write_element(std::iostream& stream, EbmlElementIDType id, uint32_t data_size)
    {
        EbmlElementID element_id = id;
        EbmlElementLength length = data_size;
        stream << element_id << length;
        Buffer buf(data_size);
        stream.write(reinterpret_cast<const char*>(buf.data()), data_size);
        stream.flush();
    }

    void run_tests()
    {
        std::fstream test_file("..\\..\\Test files\\test_file.txt", std::ios_base::binary | std::ios_base::out | std::ios_base::in | std::ios_base::trunc);
        //std::fstream test_file("..\\..\\Test files\\1.mkv", std::ios_base::binary | std::ios_base::in);
        //auto root = EbmlElement::s_construct_from_stream(test_file);
        //cout << root;
        for (uint32_t j = 0; j < 250; ++j)
        {
            test_file.seekp(0);
            EbmlElementLength len = j;
            write_element(test_file, 0x4281, j);
            test_file.seekg(0);
            BasicSharedPtr<EbmlElement> element = EbmlElement::s_construct_from_stream(test_file);
            CHECK(element->get_total_size() == element->get_data_length().get_encoded_size() + 2 + j);

            uint64_t original_element_size = element->get_total_size();
            element->overwrite_with_bool_element(0x88, true);

            CHECK(element->get_id().get_value() == 0x88);
            CHECK(element->bool_value());
            if (j == 1)
            {
                CHECK(element->get_data_length().get_encoded_size() == 2);
            }
            else if (j > 1)
            {
                element->_seek_to(EbmlOffset::End);
                BasicSharedPtr<EbmlElement> next_element = EbmlElement::s_construct_from_stream(test_file);
                CHECK(next_element->get_id().get_value() == 0xec);

                // Check that the size of both telements sums up to the size of the original element
                CHECK(next_element->get_total_size() + element->get_total_size() == original_element_size);
            }
        }
    }
}