#include <Archive.hpp>
#include <Solitaire.hpp>

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
