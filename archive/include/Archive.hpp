#pragma once

#include <Main.hpp>

class Archive : public Main
{
public:
  virtual ~Archive();
  virtual int main(const std::vector<std::string>&) override;
};
