#include <Card.hpp>

using namespace std;

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
  static const string RANK[] = { "A", "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",  "T",  "J",  "Q",  "K"};
  static const string SUIT[] = { "S", "H",  "C",  "D" };
  if (visible)
    return "[" + RANK[rank] + SUIT[suit] + "]";
  else
    return "[  ]";
}

bool Card::getColor() const
{
  return suit % 2;
}

bool Card::isSameColor(Card* card) const
{
  return card->getColor() == getColor();
}
