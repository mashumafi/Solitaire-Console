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

bool Solitaire::move()
{
    return false;
}

bool Solitaire::move(int a)
{
    return false;
}

bool Solitaire::move(int a, int b)
{
    return false;
}

string Solitaire::toString() const
{
    string ret;


    for (int i = 0; i <= King; i++)
    {
        for (int j = i; j < 7; j++)
        {
            if (tableau[j].size() > i)
            {
                ret += tableau[j].at(i)->toString();
            }
        }
        ret += "\n";
    }

    return ret;
}

ostream& operator<< (ostream& stream, Solitaire &solitaire)
{
    return stream << solitaire.toString();
}

int main()
{
    Solitaire solitaire;
    cout << solitaire << endl;
    return 0;
}
