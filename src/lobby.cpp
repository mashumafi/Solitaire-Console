#include <Solitaire.hpp>

using namespace std;

int main()
{
    Solitaire solitaire;
    do
    {
        cout << solitaire << endl;
    } while (solitaire.move() != QUIT);

    return 0;
}
