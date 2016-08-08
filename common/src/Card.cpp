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
  static const string RANK[] = { "A", "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",  "T",  "J",  "Q",  "K", "J", " "};
  static const string SUIT[] = { "S", "H",  "C",  "D" };
  string second;
  if(rank <= King)
  {
    second = SUIT[suit];
  }
  else
  {
    second = RANK[rank];
  }
  if (visible)
    return "[" + RANK[rank] + second + "]";
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

bool Card::isRed() const
{
  return getColor() == 1;
}

bool Card::isBlack() const
{
  return getColor() == 0;
}
