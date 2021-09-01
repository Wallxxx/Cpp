#include <iostream>
#include <cstdlib>
#include <ctime>

#include <termios.h>
#include <unistd.h>

class Data
{
public:
    Data(): map(nullptr) {}
    ~Data();
    bool createMap();
    bool setMap();
    bool moveUp();
    bool moveDown();
    bool moveLeft();
    bool moveRight();
    bool win();
    void printMap();
	void setInputMode(bool status);
private:
    struct cell // TODO: Выравнить
    {
        cell(): _number(0), _here(false) {}
        cell(unsigned int number, bool here): _number(number), _here(here) {}
        unsigned int _number;
        bool _here;
    };
	struct termios oldt, newt;
    cell **map;
};
