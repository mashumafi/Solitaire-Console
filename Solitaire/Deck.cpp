#include "Deck.h"

Deck::Deck() {
    for (int suit = 0; suit < Diamonds; suit++) {
        for (int rank = 0; rank < King; rank++) {
            push(new Card(rank, suit));
        }
    }
}