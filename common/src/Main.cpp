#include <Main.hpp>

using namespace std;

Main::~Main()
{
}

int Main::main(int argc, char *argv[])
{
  vector<string> args;
  for(int i = 0; i < argc; i++)
  {
    args.push_back(argv[i]);
  }
  return main(args);
}

int Main::main(const vector<string>&)
{
  return main();
}

int Main::main()
{
  return 0;
}
