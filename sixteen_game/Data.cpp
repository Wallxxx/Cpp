#include "Data.h"

Data::~Data() // Деструктор по умолчанию
{
    for (unsigned int i = 0; i < 4; i++)
    {
        delete[] map[i]; // Удаление каждой ячейки карты
    }
    delete map; // Удаление карты
}

bool Data::createMap() // Создание карты
{
    map = new cell * [4];
    for (unsigned int i = 0; i < 4; ++i) // Выделение памяти под двумерный массив
    {
        map[i] = new cell[4]; 
    }
    return true;
}

bool Data::setMap() // Заполнение карты
{
    unsigned int number = 1;
    int post = 0;
    for (unsigned int i = 0; i < 4; ++i) // Карта заполняется числами по порядку от 1 до 16
    {
        for (unsigned int q = 0; q < 4; ++q)
        {
            map[i][q]._number = number;
            number++;
        }
    }
    map[4 - 1][4 - 1]._here = true; // В нижний правый угол ставится звёздочка вместо число 16
    for (int i = 0; i < 120; i++) // Далее 120 случайных ходов в случайную сторону
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

bool Data::moveUp() // Движение вверх
{
    for (unsigned int i = 0; i < 4; ++i)
    {
        for (unsigned int q = 0; q < 4; ++q)
        {
            if (map[i][q]._here) // Поиск клетки со звёздочкой
            {
                if (i != 0) // Если есть, куда идти выше...
                { // ...перемещение выше
                    map[i][q]._here = false; // Убирается звёздочка с нынешней клетки
                    map[i - 1][q]._here = true; // Ставится в клетку выше
                    std::swap(map[i][q]._number, map[i - 1][q]._number); // Числа этих ячеек меняются местами
                    return true; // Перемещение пошло успешно
                }
                else // Иначе передвижение не удалось
                {
                    return false;
                }
            }
        }
    }
    return false;
}

bool Data::moveDown() // Передвижение вниз. Аналогично moveUp()
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

bool Data::moveLeft() // Передвижение влево. Аналогично moveUp()
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

bool Data::moveRight() // Передвижение вправо. Аналогично moveUp()
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

bool Data::win() // Проверка условия победы
{
    unsigned int number = 1;
    for (unsigned int i = 0; i < 4; ++i)
    {
        for (unsigned int q = 0; q < 4; ++q) // Проход по всем клеткам карты
        {
            if (map[i][q]._number != number) // Если числа расставлены по порядку...
            {
                return false;
            }
            number++;
        }
    }
    if (map[4 - 1][4 - 1]._here) // ...и звёздочка в конце...
    {
        return true; // ...победа
    }
    return false; // Иначе продолжение игры
}

void Data::printMap() // Печать карты
{
    for (unsigned int i = 0; i < 4; ++i)
    {
        for (unsigned int q = 0; q < 4; ++q) // Проход по всем клеткам карты
        {
            if (!map[i][q]._here) // Печать всех чисел, однако...
            {
                std::cout << map[i][q]._number << "\t";
            }
            else // ...клетка со звёздочкой печатается в виде звёздочки
            {
                std::cout << "*\t";
            }
        }
        std::cout << std::endl;
    }
}
