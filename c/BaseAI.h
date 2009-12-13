
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

