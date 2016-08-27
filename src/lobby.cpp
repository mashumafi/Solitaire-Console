#include <Archive.hpp>
#include <fp.hpp>
#include <Solitaire.hpp>
#include <fib.hpp>
#include <Tetris.hpp>

#include <limits>

using namespace std;

int main(int argc, char *argv[])
{
  Main* game;
  
  int i = 0;
  do {
    cout << "Pick a game:" << endl
         << "1. Solitaire" << endl
         << "2. Archive" << endl
         << "3. fp" << endl
         << "4. Tetris" << endl
         << "5. Meta" << endl
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
        game = new fp;
        break;
      case 4:
        game = new Tetris;
        break;
      case 5:
        cout << fib<10>() << endl;
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
  
  return 0;
}
