#include "data.h"
#include <conio.h>

using namespace std;

int main()
{
    system("cls");
    srand(time(0));
    Data game;
    game.createMap();
    game.setMap();
    game.printMap();
    int step;
    while (!game.win())
    {
        step = static_cast<int>(_getch());
        system("cls");
        if (step == 224)
        {
            step = static_cast<int>(_getch());
            switch (step)
            {
            case 72:
                game.moveUp();
                break;
            case 80:
                game.moveDown();
                break;
            case 75:
                game.moveLeft();
                break;
            case 77:
                game.moveRight();
                break;
            default:
                break;
            }
        }
        game.printMap();
    }
    cout << "You won!\n";
    return 0;
}
