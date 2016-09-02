#pragma once

#include <vector>
#include <string>

class Main
{
public:
  virtual ~Main();
  virtual int main(void);
  virtual int main(int argc, char** argv);
  virtual int main(const std::vector<std::string>&);
};
