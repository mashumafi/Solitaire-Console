#pragma once

#include <Deck.hpp>
#include <Game.hpp>

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

class Solitaire : public Game
{
private:
  Deck deck;
  std::vector<Card*> waste;
  std::vector<Card*> foundation[4];
  std::vector<Card*> tableau[7];
  int draw(void);
  int move(std::vector<Card*>&, std::vector<Card*>&, bool, Rank);
  int m_score;
  void addScore(ScoreModifier);
public:
  Solitaire();
  virtual ~Solitaire();
  
  int main();

  int move();

  int move(std::string);
  
  int move(int);

  int move(int, int);

  std::string toString() const;

  friend std::ostream& operator<< (std::ostream &out, Solitaire &solitaire);
};
