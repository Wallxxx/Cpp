//#include <iostream>
#include "StringHandler.h"
#include <fstream>

int main()
{
	StringHandler test;
	std::map<char, uint32_t> temp;
	test.addFrequency("Hello world");
	temp = test.getFrequency();
	//for (auto i : temp) std::cout << i.first << " - " << i.second << std::endl;
	std::string file;
	std::cout << "Enter path: ";
	getline(std::cin, file);
	std::ofstream _file(file, std::ios::app);
	if (_file.is_open()) std::cout << "Ok\n";
	return 0;
}