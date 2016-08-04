#pragma once

#include <vector>
#include <string>

class Game
{
public:
  virtual ~Game();
  virtual int main();
  virtual int main(int argc, char *argv[]);
  virtual int main(const std::vector<std::string>&);
};
