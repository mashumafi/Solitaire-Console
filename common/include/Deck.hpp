#pragma once

#include <Card.hpp>

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Deck : public vector<Card*>
{
public:
    Deck();
    ~Deck();
};