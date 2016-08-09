#pragma once

#include <Deck.hpp>
#include <Main.hpp>

#include <stack>
#include <iostream>
#include <string>
#include <vector>

enum ScoreModifier
{
  DECK_FLIPPED = -30,
  ADDED_TO_FOUNDATION = 30,
  REMOVED_FROM_FOUNDATION = -25
};

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

class Solitaire : public Main
{
private:
  Deck deck;
  std::vector<Card*> waste;
  std::vector<Card*> foundation[4];
  std::vector<Card*> tableau[7];
  SolitaireState draw(void);
  SolitaireState move(std::vector<Card*>&, std::vector<Card*>&, bool, Rank);
  int m_score;
  void addScore(ScoreModifier);
public:
  Solitaire();
  virtual ~Solitaire();
  
  int main();

  SolitaireState move();

  SolitaireState move(std::string);
  
  SolitaireState move(int);

  SolitaireState move(int, int);

  std::string toString() const;

  friend std::ostream& operator<< (std::ostream &out, Solitaire &solitaire);
};
