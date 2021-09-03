#pragma once
#include "StringHandler.h"

class Huffman
{
public:
	Huffman() {}
	~Huffman();
	void frequencyTableEncode(); // Таблица частот из инета
	void userFrequencyTableEncode(); // Пользовательская таблица
private:
	std::map<char, uint32_t> _frequencyTable;
	void fillingFrequencyTable();
	void fillingUserFrequencyTableEncode();
};

