#include <Game.hpp>

using namespace std;

int Game::main(int argc, char *argv[])
{
  vector<string> args;
  for(int i = 0; i < argc; i++)
  {
    args.push_back(argv[i]);
  }
  return main(args);
}

int Game::main(const vector<string>&)
{
  return main();
}

int Game::main()
{
  return 0;
}
