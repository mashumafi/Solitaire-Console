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
    void draw(void);
public:
    Solitaire();

    int move();

    int move(string);
    
    int move(int);

    int move(int, int);

    string toString() const;

    friend ostream& operator<< (ostream &out, Solitaire &solitaire);
};