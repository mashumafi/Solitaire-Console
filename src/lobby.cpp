#include <Solitaire.hpp>

using namespace std;

int main(int argc, char *argv[])
{
  Game* game;
  
  cout << "Pick a game:" << endl
       << "1. Solitaire" << endl
       << "*. Quit" << endl;
  int i = 0;
  do {
    cin >> i;
    switch(i)
    {
      case 1:
        game = new Solitaire;
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
