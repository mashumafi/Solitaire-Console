#include <Solitaire.hpp>

#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

Solitaire::Solitaire() : m_score(0)
{
  for (int i = 0; i < 7; i++)
  {
    for (int j = i; j < 7; j++)
    {
      if (i == j)
      {
        deck.back()->visible = 1;
      }
      tableau[j].push_back(deck.back());
      deck.pop_back();
    }
  }
}

Solitaire::~Solitaire()
{
}

int Solitaire::main()
{
  do
  {
    cout << *this << endl;
  } while (this->move() != QUIT);
  return 0;
}

SolitaireState Solitaire::move()
{
  string line;
  getline(cin, line);
  return move(line);
}

SolitaireState Solitaire::move(string s)
{
  try
  {
    return move(stoi(s, NULL, 16));
  }
  catch (const std::exception& e)
  {
    return INVALID_COMMAND;
  }
}

SolitaireState Solitaire::move(int a)
{
  return a < 16 ? move(a, a) : move(a / 16, a % 16);
}

SolitaireState Solitaire::move(int a, int b)
{
  // value is out of bounds
  if (a > 12 || b > 12 || a < 0 || b < 0)
  {
    if(a == 13 || b == 13)
    {
      return QUIT;
    }
    else
    {
      return INVALID_COMMAND;
    }
  }
  // draw from the deck
  if (a == 0)
  {
    return draw();
  }
  // only one value passed
  if (a == b)
  {
    // put card from tableau into foundation
    if (1 <= a && a <= 8)
    {
      // flip bottom card
      if (a >= 2 && !tableau[a - 2].back()->visible)
      {
        tableau[a - 2].back()->visible = true;
      }
      // try putting card onto foundation
      move(a, 9);
      move(a, 10);
      move(a, 11);
      move(a, 12);
      return FAILED_MOVE;
    }
    // automatically fill foundations
    if (9 <= a && a <= 12)
    {
      return FAILED_MOVE;
    }
  }
  else
  {
    // move 1 card from waste
    if (a == 1)
    {
      if (waste.empty())
      {
        return FAILED_MOVE;
      }
      // to tableau
      if (2 <= b && b <= 8)
      {
        return move(waste, tableau[b - 2], false, King);
      }
      // to foundation
      if (9 <= b && b <= 12)
      {
        SolitaireState ss = move(waste, foundation[b - 9], false, Ace);
        if(ss == SUCCESS)
        {
          addScore(ADDED_TO_FOUNDATION);
        }
        return ss;
      }
    }
    // move from tableau
    if (2 <= a && a <= 8)
    {
      // to tableau
      if (2 <= b && b <= 8)
      {
        return move(tableau[a - 2], tableau[b - 2], true, King);
      }
      // to foundation
      if (9 <= b && b <= 12)
      {
        SolitaireState ss = move(tableau[a - 2], foundation[b - 9], false, Ace);
        if(ss == SUCCESS)
        {
          addScore(ADDED_TO_FOUNDATION);
        }
        return ss;
      }
      return FAILED_MOVE;
    }
    // move from foundation
    if ((9 <= a && a <= 12))
    {
      // to tableau
      if (2 <= b && b <= 8)
      {
        SolitaireState ss = move(foundation[a - 2], tableau[b - 9], false, King);
        if(ss == SUCCESS)
        {
          addScore(REMOVED_FROM_FOUNDATION);
        }
        return ss;
      }
      // to foundation
      if (9 <= b && b <= 12)
      {
        return move(foundation[a - 9], foundation[b - 9], false, Ace);
      }
      return FAILED_MOVE;
    }
  }
  return UNKNOWN;
}

SolitaireState Solitaire::draw()
{
  if (deck.size() == 0)
  {
    if (waste.empty())
    {
      return FAILED_DRAW;
    }
    while (!waste.empty())
    {
      deck.push_back(waste.back());
      waste.pop_back();
    }
    addScore(DECK_FLIPPED);
  }
  deck.back()->visible = true;
  waste.push_back(deck.back());
  deck.pop_back();
  return SUCCESS;
}

SolitaireState Solitaire::move(vector<Card*>& a, vector<Card*>& b, bool allowMulti, Rank base)
{
  if (allowMulti)
  {
    // gonna move multiple cards (tableau to tableau)
    Card* B = NULL;
    if (!b.empty())
    {
      B = b.back();
    }
    
    for (int i = a.size() - 1; i >= 0; i--)
    {
      Card* A = a[i];
      if (!A->visible)
      {
        return FAILED_MOVE;
      }
      if (B == NULL || !B->visible)
      {
        // move tableau on empty tableau or a fliped tableau
        if (A->rank == King)
        {
          int dist = a.size() - i;
          vector<Card*> temp;
          for (int j = 0; j < dist; j++)
          {
            temp.push_back(a.back());
            a.pop_back();
          }
          while (!temp.empty())
          {
            b.push_back(temp.back());
            temp.pop_back();
          }
        }
      }
      else if (!B->isSameColor(A) && B->rank - 1 == A->rank)
      {
        // move tableau on existing tableau
        int dist = a.size() - i;
        vector<Card*> temp;
        for (int j = 0; j < dist; j++)
        {
          temp.push_back(a.back());
          a.pop_back();
        }
        while (!temp.empty())
        {
          b.push_back(temp.back());
          temp.pop_back();
        }
        return SUCCESS;
      }
    }
    return FAILED_MOVE;
  }
  else
  {
    Card* A = a.back();
    // moving 1 card
    if (b.empty() || !b.back()->visible)
    {
      // is the card allowed on an empty/flipped tableau?
      if (A->rank != base)
      {
        return FAILED_MOVE;
      }
    }
    else
    {
      Card* B = b.back();
      if (base == Ace)
      {
        // can card be moved to foundation
        if (B->suit != A->suit || B->rank != A->rank - 1)
        {
          return FAILED_MOVE;
        }
      }
      else if (base == King)
      {
        // can card be moved to tableau
        if (B->isSameColor(A) || B->rank - 1 != A->rank)
        {
          return FAILED_MOVE;
        }
      }
      else
      {
        return INVALID_COMMAND;
      }
    }
    // move the card since we haven't failed
    b.push_back(A);
    a.pop_back();
    return SUCCESS;
  }
  return UNKNOWN;
}

void Solitaire::addScore(ScoreModifier scoreModifier)
{
  m_score += scoreModifier;
  m_score = max(0, m_score);
}

string Solitaire::toString() const
{
  std::stringstream ret;
  
  ret << "[" << setfill('0') << setw(2) << deck.size() << "]";

  if (!waste.empty())
  {
    ret << waste.back()->toString();
  }
  else
  {
    ret << "[  ]";
  }
  
  ret << "    ";

  for (int i = 0; i < 4; i++)
  {
    if (!foundation[i].empty())
    {
      ret << foundation[i].back()->toString();
    }
    else
    {
      ret << "[  ]";
    }
  }

  ret << "  Quit  Score" << endl << " 00  11      99  AA  BB  CC    DD   " << m_score << endl << endl << " 22  33  44  55  66  77  88" << endl;
  
  for (unsigned int i = 0; i <= King; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      if (tableau[j].size() > i)
      {
        ret << tableau[j].at(i)->toString();
      }
      else
      {
        ret << "    ";
      }
    }
    ret << endl;
  }
  ret << "----------------------------------------" << endl;
  return ret.str();
}

ostream& operator<< (ostream& stream, Solitaire &solitaire)
{
  return stream << solitaire.toString();
}
