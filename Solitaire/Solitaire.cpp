#include "Solitaire.h"

bool Solitaire::move() {
    return false;
}

bool Solitaire::move(int a, int b) {
    return false;
}

string Solitaire::toString() {
    return to_string(deck.top()->rank);
}

ostream& operator<< (ostream& stream, Solitaire &solitaire)
{
    return stream << solitaire.toString();
}

int main() {
    Solitaire solitaire;
    cout << solitaire << endl;
    return 0;
}