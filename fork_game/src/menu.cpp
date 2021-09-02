#include "menu.h"

Menu::~Menu()
{

}

void Menu::showMenu()
{
    Window input;
    while (true)
    {
        std::cout << "Сhoice of difficulty:\n";
        std::cout << (_stage == 1 ? UNDERLINE : RESET) << "Easy" << RESET << std::endl;
        std::cout << (_stage == 2 ? UNDERLINE : RESET) << "Normal" << RESET << std::endl;
        std::cout << (_stage == 3 ? UNDERLINE : RESET) << "Hard" << RESET << std::endl;
        input.setInputMode(true);
        char choise = static_cast<char>(getchar());
        input.setInputMode(false);
        if (choise == 'w' || choise == 'W')
        {
            if (_stage != 1) _stage--;
        }
        else if (choise == 's' || choise == 'S')
        {
            if (_stage != 3) _stage++;
        }
        else
        {
            if (choise == '\n') break;
        }
        system("clear");
    }
}

std::string Menu::getWord()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    unsigned int counter = 0;
    std::string difficulty;
    switch (_stage)
    {
    case 1:
        difficulty = "easy";
        break;
    case 2:
        difficulty = "normal";
        break;
    case 3:
        difficulty = "hard";
        break;
    default:
        difficulty = "easy";
    }
    std::ifstream data("data/" + difficulty);
    if (data.is_open())
    {
        while (getline(data, difficulty)) counter++;
    }
    data.clear();
    data.seekg(0);
    counter = static_cast<unsigned int>(rand()) % counter + 1;
    if (data.is_open())
    {
        for (unsigned int i = 0; i < counter; i++) getline(data, difficulty);
    }
    data.close();
    return difficulty;
}

unsigned int Menu::getStage()
{
    return _stage;
}
