#pragma once
#include <map>
#include <string>
#include <iostream>
#include <fstream>

class StringHandler
{
public:
	StringHandler();
	~StringHandler();
	void addFrequency(std::ifstream& stream);
	//void fileReader(std::filesystem::path::)
	std::map<char, uint32_t> getFrequency() const;
private:
	std::map<char, uint32_t> _frequency;
};
