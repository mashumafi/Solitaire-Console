#include <Card.hpp>

#include <termcolor.hpp>

#include <sstream>

using namespace std;
using namespace termcolor;

Card::Card(int rank, int suit)
{
  this->rank = rank;
  this->suit = suit;
  this->visible = 0;
}

Card::~Card()
{
}

Color Card::getColor() const
{
  return static_cast<Color>(suit % 2 == 0);
}

bool Card::isSameColor(Card* card) const
{
  return card->getColor() == getColor();
}

bool Card::isRed() const
{
  return getColor() == RED;
}

bool Card::isBlack() const
{
  return getColor() == BLACK;
}

ostream& operator<< (ostream& stream, Card &card)
{
  static const string RANK[] = { "A", "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",  "T",  "J",  "Q",  "K", "J", " "};
  static const string SUIT[] = { "S", "H",  "C",  "D" };
  string second;
  if(card.rank <= King)
  {
    second = SUIT[card.suit];
  }
  else
  {
    second = RANK[card.rank];
  }
  return   (card.visible
         ? (stream << on_white << (card.suit % 2 == 0 ? grey : red) << RANK[card.rank] << second)
         : (stream << on_cyan << "  "))
        << reset;
}
