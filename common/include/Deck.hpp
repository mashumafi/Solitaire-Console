#pragma once

#include <Card.hpp>

#include <vector>
#include <iostream>
#include <string>

class Deck : public std::vector<Card*>
{
public:
    Deck();
    ~Deck();
};