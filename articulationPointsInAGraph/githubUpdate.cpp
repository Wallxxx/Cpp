#include "Graph.h"

using namespace algorithms;

int main()
{
    setlocale(0, "");

    uint64_t matrix_size, element;
    std::cout << "Введите количество вершин: ";
    std::cin >> matrix_size;

    std::vector<std::vector<uint64_t> > matrix;
    std::cout << "Введите матрицу смежности: \n";
    for (size_t i = 0; i < matrix_size; ++i)
    {
        matrix.push_back(std::vector<uint64_t>());
        for (size_t q = 0; q < matrix_size; ++q)
        {
            std::cin >> element;
            matrix[i].push_back(element);
        }
    }

    Graph articulation;
    articulation.setMatrix(matrix);
    std::cout << "Точки сочленения: ";
    for (uint64_t i = 0; i < matrix.size(); ++i)
    {
        if (articulation.articulationPoint(i)) std::cout << i + 1 << " ";
    }
    std::cout << std::endl;
    return 0;
}
