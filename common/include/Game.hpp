#pragma once

#include <vector>
#include <string>

class Game
{
public:
  virtual int main(int argc, char *argv[]);
  virtual int main(std::vector<std::string>);
};
