/**
* @file
* @brief Реализация алгоритма поиска точек сочленения в графе
* @author Wallxxx
* @date Сентябрь 2021 года
* @warning Только для Windows! Класс тестировался поверхностно, используйте на свой страх и риск
* 
* Алгоритм поиска точек сочленения в графе. Граф задаётся матрицей смежности.
* Не трудно заметить, что если убрать одну из
* вершин, то не только графически граф разделится на две/три/четрые/etc. частей,
* но и в таблице смежности нельзя будет пройти от первой вершины до последней. Принцип
* работы алгоритма немного похож на обход в глубину, но не совсем. Допустим, есть матрица:
* 0 1 0 1 1 0 0 0
* 1 0 0 0 0 0 0 0
* 0 0 0 1 0 0 0 0
* 1 0 1 0 0 0 0 1
* 1 0 0 0 0 1 0 0
* 0 0 0 0 1 0 1 1
* 0 0 0 0 0 1 0 1
* 0 0 0 1 0 1 1 0
* Видно, что вершины 1 и 4 - точки сочленения. Принцип работы алгоритма: на вход функции поступает число -
* номер вершины, которую хотим проверить. Чтобы проверить, убираем её (просто не рассматриваем её стороку и столбец).
* 0 0 0 0 0 0 0
* 0 0 1 0 0 0 0
* 0 1 0 0 0 0 1
* 0 0 0 0 1 0 0
* 0 0 0 1 0 1 1
* 0 0 0 0 1 0 1
* 0 0 1 0 1 1 0
* Начинаем обход с точки 2. Помечаем её, что уже прошли (помечаем по диагонали, т.е. matrix[1][1] (индексы идут с 0, а 
* номера вершин с 1, это нужно помнить)). Из вершины 2 никуда больше уйти нельзя => вершина 1 является точкой сочлинения. 
*/

#pragma once
#include <iostream>
#include <vector>

#define WERE 2

namespace algorithms
{

    class Graph
    {
    public:

        /**
        * @brief Конструктор по умолчанию
        */
        Graph();

        /**
        * @brief Конструктор копирования
        * @param matrix матрица смежности
        * 
        * Упрощённый вариант получения матрицы сежности
        */
        Graph(const std::vector<std::vector<uint64_t> >& matrix);

        /**
        * @brief Деструктор по умолчанию
        */
        ~Graph();

        /**
        * @brief Копирование матрицы смежности
        * @param matrix матрица смежности
        * 
        * Копирует матрицу смежности в класс для дальнейшей работы с ней
        */
        void setMatrix(const std::vector<std::vector<uint64_t> >& matrix);

        /**
        * @brief Проверка вершины
        * @param vertex номер вершины
        * 
        * return истина, если вершина является точкой сочленения. Иначе ложь
        */
        bool articulationPoint(uint64_t vertex);

    private:
        std::vector<std::vector<uint64_t> > _matrix; /// Матрица смежности
        uint64_t _counter; /// Кол-во пройденных вершин, не учитывая ту, которая проверяется

        /**
        * @brief Проверка стартовой вершины
        * @param vertex проверяемая вершина
        * 
        * Алгоритм всегда начинает обход с первой вершины. Однако если нужно проверить первую вершину,
        * то алгоритм начинает обход со второй
        */
        void checkStartVertex(uint64_t vertex);

        /**
        * @brief Обход матрицы смежности
        * @param vertex проверяемая вершина
        * 
        * Начало обхода с первого столбца
        */
        void graphPassage(uint64_t vertex);

        /**
        * @brief Отметка вершин, в которые получилось зайти
        * @param line рассматриваемый столбец
        * @param vertex проверяемая вершина
        * 
        * Проход по всем вершинам, не учитывая столбец и строку с vertex
        */
        void wereVertexs(size_t line, uint64_t vertex);

        /**
        * @brief Просмотр результата обхода
        * 
        * return истина, если получилось пройти по всем вершинам. Иначе ложь
        */
        bool isArticulationPoint();
    };

}