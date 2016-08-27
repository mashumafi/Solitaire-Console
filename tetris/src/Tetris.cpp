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
        cout << "Hello world!" << endl;
      default:
        cout << "'" << static_cast<int>(c) << "'" << endl;
    }
  } while(c != 'q');
  return 0;
}
