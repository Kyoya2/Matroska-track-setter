/*   
 *   Matroska track setter  Copyright (C) 2021  Kyoya2
 *   
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *   
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *   
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cstdlib>
#include <regex>

#include "Common.h"

DECL_EXCEPTION(InvalidTableContent);

namespace ConsoleAttributes
{
    static const string_view BlackFG         = "\x1b[30m";
    static const string_view BlackBG         = "\x1b[40m";
    static const string_view RedFG           = "\x1b[31m";
    static const string_view RedBG           = "\x1b[41m";
    static const string_view GreenFG         = "\x1b[32m";
    static const string_view GreenBG         = "\x1b[42m";
    static const string_view YellowFG        = "\x1b[33m";
    static const string_view YellowBG        = "\x1b[43m";
    static const string_view BlueFG          = "\x1b[34m";
    static const string_view BlueBG          = "\x1b[44m";
    static const string_view MagentaFG       = "\x1b[35m";
    static const string_view MagentaBG       = "\x1b[45m";
    static const string_view CyanFG          = "\x1b[36m";
    static const string_view CyanBG          = "\x1b[46m";
    static const string_view LightGrayFG     = "\x1b[37m";
    static const string_view LightGrayBG     = "\x1b[47m";
    static const string_view DarkGrayFG      = "\x1b[90m";
    static const string_view DarkGrayBG      = "\x1b[100m";
    static const string_view LightRedFG      = "\x1b[91m";
    static const string_view LightRedBG      = "\x1b[101m";
    static const string_view LightGreenFG    = "\x1b[92m";
    static const string_view LightGreenBG    = "\x1b[102m";
    static const string_view LightYellowFG   = "\x1b[93m";
    static const string_view LightYellowBG   = "\x1b[103m";
    static const string_view LightBlueFG     = "\x1b[94m";
    static const string_view LightBlueBG     = "\x1b[104m";
    static const string_view LightMagentaFG  = "\x1b[95m";
    static const string_view LightMagentaBG  = "\x1b[105m";
    static const string_view LightCyanFG     = "\x1b[96m";
    static const string_view LightCyanBG     = "\x1b[106m";
    static const string_view WhiteFG         = "\x1b[97m";
    static const string_view WhiteBG         = "\x1b[107m";
    static const string_view Underline       = "\x1b[4m";
    static const string_view NoUnderline     = "\x1b[24m";
}

class ConsoleUtils
{
public:
    inline void cls() { std::system("cls"); }
    static void print_table(string title, vector<string> headers, vector<vector<string>> rows)
    {
#define padded_text(text, padding) text << string(padding - _s_get_console_text_size(text), ' ')

        size_t num_columns = headers.size();
        if (!rows.empty() && (rows[0].size() != num_columns))
        {
            throw InvalidTableContent();
        }

        // Calculate the maximum width of each column
        vector<size_t> column_widths(num_columns);
        for (size_t col = 0; col < num_columns; ++col)
        {
            column_widths[col] = _s_get_console_text_size(headers[col]);
            for (size_t row = 0; row < rows.size(); ++row)
            {
                column_widths[col] = std::max(column_widths[col], _s_get_console_text_size(rows[row][col]));
            }
        }

        size_t table_width = std::accumulate(column_widths.cbegin(), column_widths.cend(), size_t(0)) + (num_columns - 1) * 3;

        size_t frame_width;
        string internal_padding; // padding between end of row and frame
        if (title.size() > table_width)
        {
            frame_width = title.size();
            internal_padding = string(title.size() - table_width, ' ');
        }
        else
        {
            frame_width = table_width;
        }
        frame_width += 2;

        cout << std::left;

        // frame top
        cout << u8"╔";                 
        for (size_t i = 0; i < frame_width; ++i)
            cout << u8"═";
        cout << u8"╗" << endl;

        // title
        cout << u8"║ " << padded_text(title, frame_width - 2) << u8" ║" << endl;

        // title separator
        cout << u8"╟";
        for (size_t i = 0; i < frame_width; ++i)
            cout << u8"─";
        cout << u8"╢" << endl;

        // Headers
        cout << u8"║ ";
        for (size_t col = 0; col < num_columns; ++col)
        {
            if (col != 0)
                cout << u8" │ ";

            cout << padded_text(headers[col], column_widths[col]);
        }
        cout << internal_padding << u8" ║" << endl;

        // Header separator
        cout << u8"║ ";
        for (size_t col = 0; col < num_columns; ++col)
        {
            if (col != 0)
                cout << u8"─┼─";

            for (size_t i = 0; i < column_widths[col]; ++i)
                cout << u8"─";
        }
        cout << internal_padding << u8" ║" << endl;

        // Rows
        for (size_t row = 0; row < rows.size(); ++row)
        {
            cout << u8"║ ";
            for (size_t col = 0; col < num_columns; ++col)
            {
                if (col != 0)
                    cout << u8" │ ";

                cout << padded_text(rows[row][col], column_widths[col]);
            }
            cout << internal_padding << u8" ║" << endl;
        }
#undef padded_text

        // frame bottom
        cout << u8"╚";
        for (size_t i = 0; i < frame_width; ++i)
            cout << u8"═";
        cout << u8"╝" << endl;
    }

private:
    static size_t _s_get_console_text_size(const string& text)
    {   //
        //\x1b[100mBLA\x1b[4m
        static const std::regex COLORED_TEXT("^\x1b\\[\\d{1,3}m.*\x1b\\[\\d{1,3}m$");

        if (std::regex_search(text, COLORED_TEXT))
        {
            return text.rfind('\x1b') - text.find('m') - 1;
        }
        return text.size();
    }
};