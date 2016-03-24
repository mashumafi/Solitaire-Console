#pragma once

#include <vector>
#include "Card.h"

using namespace std;

class Deck : public vector<Card*>
{
public:
    Deck();
    ~Deck();
};