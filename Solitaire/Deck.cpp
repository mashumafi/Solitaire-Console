#include "Deck.h"

Deck::Deck() {
    for (int suit = Spades; suit <= Diamonds; suit++)
    {
        for (int rank = Ace; rank <= King; rank++)
        {
            push_back(new Card(rank, suit));
        }
    }
}

Deck::~Deck()
{
    for (int i = 0; i < size(); i++)
    {
        delete at(i);
    }
}
