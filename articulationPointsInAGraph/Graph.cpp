#include "Graph.h"

namespace algorithms
{

    Graph::Graph() // Конструктор по молчанию
    {
        _counter = 0;
    }

    Graph::Graph(const std::vector<std::vector<uint64_t> >& matrix) // Конструктор копирования
    {
        _matrix = matrix;
    }

    Graph::~Graph() // Деструктор по умолчанию
    {
        for (auto vectors : _matrix) vectors.clear(); // Отчистка всех подвекторов (нужна ли эта строка или нет: под вопросом)
        _matrix.clear(); // Отчистка самого вектора
    }

    void Graph::setMatrix(const std::vector<std::vector<uint64_t> >& matrix) // Копирование матрицы смежности
    {
        _matrix = matrix;
    }

    bool Graph::articulationPoint(uint64_t vertex) // Проверка, является ли вершина точкой сочленения
    {
        checkStartVertex(vertex); // Установка начала обхода
        graphPassage(vertex); // Обход матрицы
        return isArticulationPoint(); // True или False по результатам обхода
    }

    void Graph::checkStartVertex(uint64_t vertex) // Установка начала обхода
    {
        _counter = 0; // Счётчик пройдёных вершин
        _matrix[0][0] = WERE; // Начало алгоритма из (0, 0), однако...
        if (vertex == 0) _matrix[1][1] = WERE; // ...если проверяется (0, 0), то начало становится (1, 1)
    }

    void Graph::graphPassage(uint64_t vertex) // Обход матрицы
    {
        for (size_t i = 0; i < _matrix.size(); ++i) // Проход по столбцам
        {
            if (_matrix[i][i] == WERE) wereVertexs(i, vertex); // Если в этой вершине были...
        }
    }

    void Graph::wereVertexs(size_t line, uint64_t vertex) // ...поиск следующих вершин, куда можно зайти:
    {
        for (size_t q = 0; q < _matrix.size(); ++q) // - проход по всему столбцу
        {
            if ((_matrix[q][line] == 1) && (line != vertex) && (q != vertex)) _matrix[q][q] = WERE; // - если можно пройти, ставится отметка
        }
    }

    bool Graph::isArticulationPoint() // Подсчёт кол-ва пройденных вершин
    {
        for (size_t i = 0; i < _matrix.size(); ++i) // Смотрится главная диагональ...
        {
            if (_matrix[i][i] == WERE) { _counter++; _matrix[i][i] = 0; } // ...и считается кол-во посещённых вершин
        }
        if (_counter >= _matrix.size() - 1) return false; // Если кол-во >= (кол-во всех вершин, но на единицу меньше), то...
        else return true; // ...получилось пройти по всем вершинам. Проверяемая вершина не является точкой сочленения. Иначе - является.
    }

}