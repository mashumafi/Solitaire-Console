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
    char buffer[3];
    cin.getline(buffer, 3);

    bool ret = move(string(buffer));
    cin.clear();

    return ret;
}

bool Solitaire::move(string s)
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

bool Solitaire::move(int a)
{
    return a < 16 ? move(a, a) : move(a / 16, a % 16);
}

bool Solitaire::move(int a, int b)
{
    cout << "a:" + to_string(a) + ",b:" + to_string(b) << endl;
    return false;
}

string Solitaire::toString() const
{
    string ret;
    
    char deck_size[3];
    sprintf(deck_size, "%02d", deck.size());
    ret += "[" + string(deck_size) + "]";

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
        solitaire.move();
    }

    return 0;
}
