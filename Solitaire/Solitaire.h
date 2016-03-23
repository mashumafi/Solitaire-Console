#pragma once

#include "Deck.h"
#include <stack>
#include <iostream>
#include <string>

using namespace std;

class Solitaire {
private:
    stack<Card*> deck;
    stack<Card*> waste;
    stack<Card*> foundation[4];
    stack<Card*> tableau[7];
public:
    bool move();
    
    bool move(int);

    bool move(int, int);

    string toString();

    friend ostream& operator<< (ostream &out, Solitaire &solitaire);
};