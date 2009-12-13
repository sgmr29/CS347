
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


