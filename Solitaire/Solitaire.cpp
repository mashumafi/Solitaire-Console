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
            // to tableau
            if (2 <= b && b <= 8)
            {
                return move(waste, tableau[b - 2], false, King);
            }
            // to foundation
            if (9 <= b && b <= 12)
            {
                return move(waste, foundation[b - 9], false, Ace);
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
                return move(tableau[a - 2], foundation[b - 9], false, Ace);
            }
            return FAILED_MOVE;
        }
        // move from foundation
        if ((9 <= a && a <= 12))
        {
            // to tableau
            if (2 <= b && b <= 8)
            {
                return move(foundation[a - 2], tableau[b - 9], false, King);
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

int Solitaire::move(vector<Card*>& a, vector<Card*>& b, bool allowMulti, Rank base)
{
    if (allowMulti)
    {
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
        if (b.empty() || !b.back()->visible)
        {
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
                if (B->suit != A->suit || B->rank != A->rank - 1)
                {
                    return FAILED_MOVE;
                }
            }
            else if (base == King)
            {
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
        b.push_back(A);
        a.pop_back();
        return SUCCESS;
    }
    return 0;
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
