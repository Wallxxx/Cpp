#pragma once
#include <map>
#include <string>
#include <iostream>
#include <filesystem>

class StringHandler
{
public:
	StringHandler();
	~StringHandler();
	void addFrequency(const std::string& input);
	//void fileReader(std::filesystem::path::)
	std::map<char, uint32_t> getFrequency();
private:
	std::map<char, uint32_t> _frequency;
};
