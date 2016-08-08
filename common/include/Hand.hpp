#pragma once

#include <vector>

class Hand : public std::vector<Card*>
{
public:
  virtual ~Hand();
};
