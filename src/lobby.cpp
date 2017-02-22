#include <Archive.hpp>
#include <Solitaire.hpp>
#include <Tetris.hpp>
#include <Number.hpp>

#include <limits>

using namespace std;

int main(int argc, char** argv)
{
  Main* game;
  
  int i = 0;
  do {
    cout << "Pick a game:" << endl
         << "1. Solitaire" << endl
         << "2. Archive" << endl
         << "3. Tetris" << endl
         << "*. Quit" << endl;
    cin >> i;
    cin.clear();
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); 
    game = nullptr;
    switch(i)
    {
      case 1:
        game = new Solitaire;
        break;
      case 2:
        game = new Archive;
        break;
      case 3:
        game = new Tetris;
        break;
      default:
        i = 0;
        break;
    }
    if(game != nullptr)
    {
      game->main(argc, argv);
      delete game;
    }
  } while (i != 0);
  
  Integer j(10);
  Float f = 5;
  f = f + f;
  f = f - f;
  f = f * f;
  f = f / f;
  Byte asdf = 1;
  asdf++;
  Short sh;
  sh--;
  Integer n(4);
  cout << n << ' ' << (n^N(2.51)).sqrt() << endl;
  
  return 0;
}
