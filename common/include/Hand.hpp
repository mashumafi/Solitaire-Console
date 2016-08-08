#pragma once

#include <Card.hpp>

#include <vector>

class Hand : public std::vector<Card*>
{
public:
  virtual ~Hand();
};
