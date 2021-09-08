#include "Huffman.h"

Huffman::Huffman()
{
	handler = nullptr;
}

Huffman::~Huffman()
{
	delete handler;
}

void Huffman::encode(std::string& file)
{
	handler = new StringHandler;
	openStream(file);
	_frequencyTable = handler->getFrequency();

	///////  DEBUG  ///////
	
	for (auto i : _frequencyTable) std::cout << i.first << " - " << i.second << std::endl;

	///////////////////////

	Tree tree;
	for (auto i : _frequencyTable)
	{
		tree.addToTree(i.second, i.first);
	}
	
}



void Huffman::openStream(std::string& file)
{
	std::ifstream stream(file);
	handler->addFrequency(stream);
}