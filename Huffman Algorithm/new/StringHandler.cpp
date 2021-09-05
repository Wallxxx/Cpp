#include "StringHandler.h"

StringHandler::StringHandler()
{
	_frequency.clear();
}

StringHandler::~StringHandler()
{
	_frequency.clear();
}

void StringHandler::addFrequency(std::ifstream& stream)
{
	std::string line_from_file;
	while (getline(stream, line_from_file))
	{
		for (auto letter : line_from_file) _frequency[letter] += 1;
	}
}

std::map<char, uint32_t> StringHandler::getFrequency() const
{
	return _frequency;
}
