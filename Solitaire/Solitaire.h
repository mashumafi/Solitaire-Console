#pragma once

#include "Deck.h"
#include <stack>
#include <iostream>
#include <string>

using namespace std;

class Solitaire
{
private:
    Deck deck;
    stack<Card*> waste;
    stack<Card*> foundation[4];
    vector<Card*> tableau[7];
public:
    Solitaire();

    bool move();
    
    bool move(int);

    bool move(int, int);

    string toString() const;

    friend ostream& operator<< (ostream &out, Solitaire &solitaire);
};