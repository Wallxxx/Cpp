#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <vector>

namespace algorithms
{

	class Huffman
	{
	public:
		Huffman();
		~Huffman();
		void encode(std::string& in_file, std::string& out_file);
	private:
		struct unit
		{
			unit();
			unit(char symbol, uint32_t symbol_frequency);
			unit(unit* left, unit* right);
			uint32_t _symbol_frequency;
			char _symbol;
			unit* _left = nullptr, * _right = nullptr;
		};
		struct compare
		{
			bool operator()(const unit* left, const unit* right) const
			{
				return left->_symbol_frequency < right->_symbol_frequency;
			}
		};
		std::map<char, uint32_t> _frequency;
		std::map<char, std::vector<bool>> _summary_table;
		std::list<unit*> _frequency_table;
		std::vector<bool> _way;
		unit* root;
		uint32_t _all_symbols;
		uint32_t _various_symbols;

		void stringHandlerOpenStreamRead(std::string& in_file);
		void stringHandlerReader(std::ifstream& in_stream);
		void stringHandlerFilling(std::string& line_from_file);

		void stringHandlerOpenStreamWrite(std::string& in_file, std::string& out_file);
		void stringHandlerReader(std::ifstream& in_file, std::ofstream& out_file);

		void makeTable();
		void makeTableTree();
		unit* makeTableTreeNodes();
		void makeWay(unit* start);

		void saveKey();
		void saveKeyAllSymbolsAmount(std::ofstream& key_file, uint32_t amount);
		void saveKeyAllSymbols(std::ofstream& key_file);

		void writeEncodeFile(std::ofstream& out_file);
	};

}