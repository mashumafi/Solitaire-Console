#pragma once

#include "Deck.h"
#include <stack>
#include <iostream>
#include <string>

using namespace std;

enum SolitaireState
{
    SUCCESS,
    FAILED_MOVE,
    FAILED_DRAW,
    INVALID_COMMAND,
    GAME_ENDED,
    UNKNOWN
};

class Solitaire
{
private:
    Deck deck;
    stack<Card*> waste;
    stack<Card*> foundation[4];
    vector<Card*> tableau[7];
    int draw(void);
public:
    Solitaire();

    int move();

    int move(string);
    
    int move(int);

    int move(int, int);

    string toString() const;

    friend ostream& operator<< (ostream &out, Solitaire &solitaire);
};