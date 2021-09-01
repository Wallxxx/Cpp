#include "data.h"

using namespace std;

int main()
{
	system("clear");
    srand(time(0));
    Data game;
    game.createMap();
    game.setMap();
    game.printMap();
    char step;
    while (!game.win())
    {
		game.setInputMode(true);
        step = static_cast<char>(getchar());
		game.setInputMode(false);
        system("clear");
        switch (step)
        {
        case 'w':
            game.moveUp();
            break;
        case 's':
            game.moveDown();
            break;
        case 'a':
            game.moveLeft();
            break;
        case 'd':
            game.moveRight();
            break;
        default:
            break;
        }
        game.printMap();
    }
    cout << "You won!\n";
    return 0;
}
