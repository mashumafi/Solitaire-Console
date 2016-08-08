#include <Deck.hpp>
#include <Random.hpp>

using namespace std;

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
  for (unsigned int i = 0; i < size(); i++)
  {
    delete at(i);
  }
}

void Deck::shuffle()
{
  Random r;
  for(int i = 0; i < size(); i++)
  {
    Card* temp = at(i);
    int j = r.nextInt(i, size() - i);
    at(i) = at(j);
    at(j) = temp;
  }
}
