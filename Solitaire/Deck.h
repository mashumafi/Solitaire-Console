#pragma once

#include <stack>
#include "Card.h"

using namespace std;

class Deck : public stack<Card*> {
public:
    Deck();
};