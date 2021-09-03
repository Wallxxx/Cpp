#include "StringHandler.h"

StringHandler::StringHandler()
{
	_frequency.clear();
}

StringHandler::~StringHandler()
{
	_frequency.clear();
}

void StringHandler::addFrequency(const std::string& input)
{
	for (auto letter : input) _frequency[letter] += 1;
}

std::map<char, uint32_t> StringHandler::getFrequency()
{
	return _frequency;
}
