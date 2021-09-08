#pragma once
#include "StringHandler.h"
#include "Tree.h"

class Huffman
{
public:
	Huffman();
	~Huffman();
	void encode(std::string& file);
private:
	StringHandler* handler;
	std::map<char, uint32_t> _frequencyTable;
	void openStream(std::string& file);
};
