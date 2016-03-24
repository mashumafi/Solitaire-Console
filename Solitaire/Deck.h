#pragma once

#include <vector>
#include "Card.h"
#include <iostream>
#include <string>

using namespace std;

class Deck : public vector<Card*>
{
public:
    Deck();
    ~Deck();
};