"""
    Matroska track setter  Copyright (C) 2022  Kyoya2

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
import random
for i in range(8):
    lower = 2**(7*i)
    upper = 2**(7*(i+1))-1
    crnt_set = set()
    while len(crnt_set) != 8:
        crnt_set.add(random.randint(lower+1, upper-1))
    string = repr([f'(uint64_t)1 << (7*{i})', f'((uint64_t)1 << (7*{i+1})) - 1'] + sorted(crnt_set)).replace("'",'')
    print('{' + string[1:-1] + '}', end=',\n')