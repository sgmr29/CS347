/*
    This file is part of CS347Backgammon.

    CS347Backgammon is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    CS347Backgammon is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with CS347Backgammon.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <iostream>
using namespace std;

class BaseAI
{
  public:
  BaseAI(){term=0;};
  void console(int sd);
  void parse(string input);
  void takeTurn();

  int term;
};

