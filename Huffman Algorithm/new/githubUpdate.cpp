//#include <iostream>
#include "Huffman.h"
#include <fstream>

int main()
{
	std::cout << "Enter path: ";
	std::string temp;
	std::string out = "none";
	std::cin >> temp;
	algorithms::Huffman test;
	test.encode(temp, out);
	//for (auto i : temp) std::cout << i.first << " - " << i.second << std::endl;
	return 0;
}
