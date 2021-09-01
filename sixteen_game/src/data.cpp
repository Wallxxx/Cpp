#include "data.h"

Data::~Data()
{
    for (unsigned int i = 0; i < 4; i++)
    {
        delete[] map[i];
    }
    delete map;
}

bool Data::createMap()
{
    map = new cell*[4];
    for (unsigned int i = 0; i < 4; ++i)
    {
        map[i] = new cell[4];
    }
    return true;
}

bool Data::setMap()
{
    unsigned int number = 1;
    int post = 0;
    for (unsigned int i = 0; i < 4; ++i)
    {
        for (unsigned int q = 0; q < 4; ++q)
        {
            map[i][q]._number = number;
            number++;
        }
    }
    map[4 - 1][4 - 1]._here = true;
    for (int i = 0; i < 120; i++)
    {
        post = rand() % 4 + 1;
        switch (post)
        {
        case 1:
            moveUp();
            break;
        case 2:
            moveDown();
            break;
        case 3:
            moveLeft();
            break;
        case 4:
            moveRight();
            break;
        }
    }
    return true;
}

bool Data::moveUp()
{
    for (unsigned int i = 0; i < 4; ++i)
    {
        for (unsigned int q = 0; q < 4; ++q)
        {
            if (map[i][q]._here)
            {
                if (i != 0)
                {
                    map[i][q]._here = false;
                    map[i - 1][q]._here = true;
                    std::swap(map[i][q]._number, map[i - 1][q]._number);
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }
    return false;
}

bool Data::moveDown()
{
    for (unsigned int i = 0; i < 4; ++i)
    {
        for (unsigned int q = 0; q < 4; ++q)
        {
            if (map[i][q]._here)
            {
                if (i != 3)
                {
                    map[i][q]._here = false;
                    map[i + 1][q]._here = true;
                    std::swap(map[i][q]._number, map[i + 1][q]._number);
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }
    return false;
}

bool Data::moveLeft()
{
    for (unsigned int i = 0; i < 4; ++i)
    {
        for (unsigned int q = 0; q < 4; ++q)
        {
            if (map[i][q]._here)
            {
                if (q != 0)
                {
                    map[i][q]._here = false;
                    map[i][q - 1]._here = true;
                    std::swap(map[i][q]._number, map[i][q - 1]._number);
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }
    return false;
}

bool Data::moveRight()
{
    for (unsigned int i = 0; i < 4; ++i)
    {
        for (unsigned int q = 0; q < 4; ++q)
        {
            if (map[i][q]._here)
            {
                if (q != 3)
                {
                    map[i][q]._here = false;
                    map[i][q + 1]._here = true;
                    std::swap(map[i][q]._number, map[i][q + 1]._number);
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }
    return false;
}

bool Data::win()
{
    unsigned int number = 1;
    for (unsigned int i = 0; i < 4; ++i)
    {
        for (unsigned int q = 0; q < 4; ++q)
        {
            if (map[i][q]._number != number)
            {
                return false;
            }
            number++;
        }
    }
    if (map[4 - 1][4 - 1]._here)
    {
        return true;
    }
    return false;
}

void Data::printMap()
{
    for (unsigned int i = 0; i < 4; ++i)
    {
        for (unsigned int q = 0; q < 4; ++q)
        {
            if (!map[i][q]._here)
            {
                std::cout << map[i][q]._number << "\t";
            }
            else
            {
                std::cout << "*\t";
            }
        }
        std::cout << std::endl;
    }
}

void Data::setInputMode(bool status)
{
    if (status)
    {
        /*tcgetattr gets the parameters of the current terminal
        STDIN_FILENO will tell tcgetattr that it should write the settings
        of stdin to oldt*/
        tcgetattr( STDIN_FILENO, &oldt);
        /*now the settings will be copied*/
        newt = oldt;

        /*ICANON normally takes care that one line at a time will be processed
        that means it will return if it sees a "\n" or an EOF or an EOL*/
        newt.c_lflag &= ~(ICANON);

        /*Those new settings will be set to STDIN
        TCSANOW tells tcsetattr to change attributes immediately. */
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }
    else
    {
        /*restore the old settings*/
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}
