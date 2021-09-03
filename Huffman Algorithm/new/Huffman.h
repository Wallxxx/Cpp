#pragma once
#include "StringHandler.h"

class Huffman
{
public:
	Huffman() {}
	~Huffman();
	void frequencyTableEncode(); // ������� ������ �� �����
	void userFrequencyTableEncode(); // ���������������� �������
private:
	std::map<char, uint32_t> _frequencyTable;
	void fillingFrequencyTable();
	void fillingUserFrequencyTableEncode();
};

