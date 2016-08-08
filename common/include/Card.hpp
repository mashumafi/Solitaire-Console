#pragma once

#include <string>

enum Suit
{
  Spades = 0,
  Hearts = 1,
  Clubs = 2,
  Diamonds = 3
};

enum Rank
{
  Ace = 0,
  Two = 1,
  Three = 2,
  Four = 3,
  Five = 4,
  Six = 5,
  Seven = 6,
  Eight = 7,
  Nine = 8,
  Ten = 9,
  Jack = 10,
  Queen = 11,
  King = 12,
  Joker = 13,
  Blank = 14
};

class Card
{
public:
  unsigned int rank : 4;
  unsigned int suit : 2;
  unsigned int visible : 1;

  Card(int, int);
  virtual ~Card();
  std::string toString(void) const;
  bool getColor(void) const;
  bool isSameColor(Card*) const;
  bool isRed(void) const;
  bool isBlack(void) const;
};
