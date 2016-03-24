#include "Solitaire.h"

Solitaire::Solitaire()
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

int Solitaire::move()
{
    char buffer[3];
    cin.getline(buffer, 3);

    bool ret = move(string(buffer));
    cin.clear();

    return ret;
}

int Solitaire::move(string s)
{
    try
    {
        return move(stoi(s, NULL, 16));
    }
    catch (const std::exception& e)
    {
        return false;
    }
}

int Solitaire::move(int a)
{
    return a < 16 ? move(a, a) : move(a / 16, a % 16);
}

int Solitaire::move(int a, int b)
{
    // value is out of bounds
    if (a > 12 || b > 12 || a < 0 || b < 0)
    {
        return INVALID_COMMAND;
    }
    // draw from the deck
    if (a == 0)
    {
        return draw();
    }
    // only one value passed
    if (a == b)
    {
        // auto place on tableau
        if (a == 1)
        {
            return FAILED_MOVE;
        }
        // put card from tableau into foundation
        if (a <= 2 && a <= 8)
        {
            return FAILED_MOVE;
        }
        // automatically fill foundations
        if (a <= 9 && a <= 12)
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
            // move to tableau
            if (2 <= b && b <= 8)
            {
                Card* A = waste.back();
                Card* B = tableau[b - 2].back();
                if (!B->isSameColor(A) && B->rank - 1 == A->rank)
                {
                    tableau[b - 2].push_back(waste.back());
                    waste.pop_back();
                    return SUCCESS;
                }
                return FAILED_MOVE;
            }
            // move to foundation
            if (9 <= b && b <= 12)
            {
                Card* A = waste.back();
                if (foundation[b - 9].empty())
                {
                    if (A->rank != Ace)
                    {
                        return FAILED_MOVE;
                    }
                }
                else
                {
                    Card* B = foundation[b - 9].back();
                    if (B->suit != A->suit || B->rank != A->rank - 1)
                    {
                        return FAILED_MOVE;
                    }
                }
                foundation[b - 9].push_back(A);
                waste.pop_back();
                return SUCCESS;
            }
        }
        // move from tableau to another tableau
        if ((2 <= a && a <= 8) && (2 <= b && b <= 8))
        {
            return FAILED_MOVE;
        }
        // move from foundation to another foundation
        if ((9 <= a && a <= 12) && (2 <= b && b <= 8))
        {
            return FAILED_MOVE;
        }
        // move from tableau to foundation
        if ((2 <= a && a <= 8) && (9 <= b && b <= 12))
        {
            return FAILED_MOVE;
        }
        // move from foundation to tableau
        if ((9 <= a && a <= 12) && (2 <= b && b <= 8))
        {
            return FAILED_MOVE;
        }
    }
    return UNKNOWN;
}

int Solitaire::draw()
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
    }
    deck.back()->visible = true;
    waste.push_back(deck.back());
    deck.pop_back();
    return SUCCESS;
}

string Solitaire::toString() const
{
    string ret;
    
    char deck_size[3];
    sprintf(deck_size, "%02d", deck.size());
    ret += "[" + string(deck_size) + "]";

    if (!waste.empty())
    {
        ret += waste.back()->toString();
    }
    else
    {
        ret += "[  ]";
    }
    
    ret += "    ";

    for (int i = 0; i < 4; i++)
    {
        if (!foundation[i].empty())
        {
            ret += foundation[i].back()->toString();
        }
        else
        {
            ret += "[  ]";
        }
    }

    ret += "\n 00  11      99  AA  BB  CC\n\n 22  33  44  55  66  77  88\n";
    
    for (int i = 0; i <= King; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (tableau[j].size() > i)
            {
                ret += tableau[j].at(i)->toString();
            }
            else
            {
                ret += "    ";
            }
        }
        ret += "\n";
    }
    ret += "----------------------------------------\n";
    return ret;
}

ostream& operator<< (ostream& stream, Solitaire &solitaire)
{
    return stream << solitaire.toString();
}

int main()
{
    Solitaire solitaire;
    do
    {
        cout << solitaire << endl;
    } while (solitaire.move() != QUIT);

    return 0;
}
