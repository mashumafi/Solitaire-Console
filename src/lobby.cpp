#include <Solitaire.hpp>

using namespace std;

int main(int argc, char *argv[])
{
  Game* game;
  
  game = new Solitaire;
  
  game->main(argc, argv);
  
  return 0;
}
