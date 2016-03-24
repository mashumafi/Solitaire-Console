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
    if (a == 0)
    {

    }
    return false;
}

bool Solitaire::move(int a, int b)
{
    return false;
}

string Solitaire::toString() const
{
    string ret;
    
    if (deck.back() != NULL)
    {
        ret += "[  ]";
    }
    else
    {
        ret += "    ";
    }

    if (!waste.empty())
    {
        ret += waste.top()->toString();
    }
    else
    {
        ret += "    ";
    }
    
    ret += "    ";

    for (int i = 0; i < 4; i++)
    {
        if (!foundation[i].empty())
        {
            ret += foundation[i].top()->toString();
        }
        else
        {
            ret += "    ";
        }
    }

    ret += "\n";
    
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
    int a = 0, b = 0;

    while (a != -1)
    {
        cout << solitaire << endl;
        cin >> a;
        if (cin.rdbuf()->in_avail())
        {
            cin >> b;
            solitaire.move(a, b);
            cout << "move(" + to_string(a) + "," + to_string(b) + ")\n";
        }
        else
        {
            solitaire.move(a);
            cout << "move(" + to_string(a) + ")\n";
        }
    }

    return 0;
}
