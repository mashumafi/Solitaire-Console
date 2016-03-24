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
        return false;
    }
    // draw from the deck
    if (a == 0)
    {
        draw();
        return true;;
    }
    // only one value passed
    if (a == b)
    {
        // draw a card
        if (a == 1)
        {
            draw();
            return true;
        }
        // put card from tableau into foundation
        if (a <= 2 && a <= 8)
        {

        }
    }
    else
    {
    }
    return false;
}

void Solitaire::draw()
{
    deck.back()->visible = true;
    waste.push(deck.back());
    deck.pop_back();
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
        ret += "[  ]";
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
    int a = 0, b = 0;

    while (a != -1)
    {
        cout << solitaire << endl;
        solitaire.move();
    }

    return 0;
}
