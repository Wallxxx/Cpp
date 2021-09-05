//#include <iostream>
#include "Huffman.h"
#include <fstream>

int main()
{
	std::cout << "Enter path: ";
	std::string temp;
	std::cin >> temp;
	Huffman test;
	test.encode(temp);
	//for (auto i : temp) std::cout << i.first << " - " << i.second << std::endl;
	return 0;
}
