#ifndef MENU_H
#define MENU_H

#include "window.h"
#include <fstream>
#include <ctime>

class Menu
{
public:
    Menu(): _stage(1) {}
    ~Menu();
    void showMenu();
    unsigned int getStage();
    std::string getWord();
private:
    unsigned int _stage;
};

#endif // MENU_H
