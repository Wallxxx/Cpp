//#include <iostream>
#include "Huffman.h"
#include <fstream>

int main()
{
	std::cout << "Enter path': ";
	std::string ein = "test.txt";
	std::string eout = "none.txt";


	std::string din = "none.txt";
	std::string dout = "original.txt";
	std::string dkey = "key.txt";
	//std::cin >> temp;
	algorithms::Huffman test;
	//test.encode(temp, out);
	// 
	test.encode(ein, eout);
	test.decode(din, dout, dkey);


	//for (auto i : temp) std::cout << i.first << " - " << i.second << std::endl;
	return 0;
}
