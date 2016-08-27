#include <Tetris.hpp>
#include <Keyboard.hpp>

#include <iostream>

using namespace std;

Tetris::~Tetris()
{
}

int Tetris::main(const vector<string>&)
{
  char c;
  do
  {
    c = getkey();
    switch(c)
    {
      case 'a':
        break;
      case 's':
        break;
      case 'd':
        break;
    }
  } while(c != 'q');
  return 0;
}
