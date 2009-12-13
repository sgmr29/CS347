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


#include "client.h"
#include "BaseAI.h"

#include <iostream>
using namespace std;


void BaseAI::console(int sd)
{
  char buf[1024];
  int i, c;
    while (1)
    {
      buf[0] = '\r';
      buf[1] = '\n';
      buf[2] = '\0';
      c = getchar();
      i = 0;
      while(c != '\n')
      {
        //printf("i : %d\n", i);
        buf[i] = (char)c;
        buf[i+1] = '\r';
        buf[i+2] = '\n';
        buf[i+3]= '\0';
        //putchar(c);
        i = i + 1;
        c = getchar();
      }
      printf("WRITING : %s\n", buf);
      write(sd, buf, i+2);

    }
}


void BaseAI::parse(string input)
{
  cout << "Parsed " << input << endl;
}


