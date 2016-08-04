#include <Solitaire.hpp>

int main()
{
    Solitaire solitaire;
    do
    {
        cout << solitaire << endl;
    } while (solitaire.move() != QUIT);

    return 0;
}
