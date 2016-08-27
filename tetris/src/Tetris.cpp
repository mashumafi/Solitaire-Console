#include <Tetris.hpp>
#include <Keyboard.hpp>

#include <iostream>

using namespace std;

Tetris::~Tetris()
{
}

int Tetris::main(const vector<string>&)
{
  char c = getkey();
  switch(c)
  {
    case 'a':
      cout << "Hello world!" << endl;
    default:
      cout << "'" << c << "'" << endl;
  }
  return 0;
}
