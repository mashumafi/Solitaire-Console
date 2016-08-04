#pragma once

#include <Deck.hpp>

#include <stack>
#include <iostream>
#include <string>
#include <vector>

enum SolitaireState
{
    SUCCESS,
    FAILED_MOVE,
    FAILED_DRAW,
    INVALID_COMMAND,
    GAME_ENDED,
    QUIT,
    UNKNOWN
};

class Solitaire
{
private:
    Deck deck;
    std::vector<Card*> waste;
    std::vector<Card*> foundation[4];
    std::vector<Card*> tableau[7];
    int draw(void);
    int move(std::vector<Card*>&, std::vector<Card*>&, bool, Rank);
public:
    Solitaire();

    int move();

    int move(std::string);
    
    int move(int);

    int move(int, int);

    std::string toString() const;

    friend std::ostream& operator<< (std::ostream &out, Solitaire &solitaire);
};
