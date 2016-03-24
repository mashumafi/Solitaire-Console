#include "Card.h"

Card::Card(int rank, int suit)
{
    this->rank = rank;
    this->suit = suit;
    this->visible = 0;
}

Card::~Card()
{

}

string Card::toString() const
{
    if (visible)
        return "[" + to_string("A23456789TJQK"[rank]) + to_string("SHCD"[suit]) + "]";
    else
        return "[  ]";
}
