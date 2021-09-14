//#include <iostream>
#include "Huffman.h"
#include <fstream>

int main()
{
	std::cout << "Enter path: ";
	std::string ein = "temp.txt";
	std::string eout = "none.txt";


	std::string din = "none.txt";
	std::string dout = "original.txt";
	std::string dkey = "key.txt";
	//std::cin >> temp;
	algorithms::Huffman test;
	//test.encode(temp, out);
	// 
	//test.encode(ein, eout);
	//test.decode(din, dout, dkey);


	std::ifstream temp(ein);
	char value;
	while (!temp.eof())
	{
		value = temp.get();
		std::cout << value << std::endl;

	}
	
	//for (auto i : temp) std::cout << i.first << " - " << i.second << std::endl;
	return 0;
}
