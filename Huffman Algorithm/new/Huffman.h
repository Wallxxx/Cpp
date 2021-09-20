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
		void decode(std::string& in_file, std::string& out_file, std::string& key_file);
	private:
		struct unit
		{
			unit();
			unit(char symbol, uint32_t symbol_frequency);
			unit(unit* left, unit* right);
			~unit();
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
		unit* _root;
		unit* _iterator;
		uint32_t _all_symbols;
		uint32_t _write_symbols;
		uint32_t _various_symbols;
		uint16_t _key_symbols;
		uint8_t _encode_value;
		uint8_t _bits;
		uint8_t _degree;
		char _letter;

		void stringHandlerOpenStreamRead(std::string& in_file);
		void stringHandlerReader(std::ifstream& in_stream);
		void stringHandlerFilling(std::ifstream& in_stream);

		void stringHandlerOpenStreamWrite(std::string& in_file, std::string& out_file);
		void stringHandlerReader(std::ifstream& in_file, std::ofstream& out_file);
		void stringHandlerReaderEncode(std::ofstream& out_file, const char letter);
		void stringHandlerReaderEncodeWrite(std::ofstream& out_file);

		void makeTable();
		void makeTableTree();
		unit* makeTableTreeNodes();
		void makeWay(unit* start);

		void saveKey();
		void saveKeyAllSymbolsAmount(std::ofstream& key_file, uint32_t amount);
		void saveKeyAllSymbols(std::ofstream& key_file);

		void stringHandlerOpenStreamRead(std::string& in_file, std::string& key_file);
		void stringHandlerOpenStreamReadAllSymbols(std::ifstream& key_stream);
		void stringHandlerOpenStreamReadVariousSymbols(std::ifstream& key_stream);
		void stringHandlerOpenStreamReadCodes(std::ifstream& key_stream);

		void makeTree(std::ifstream& key_stream);
		void makeTreeLeft();
		void makeTreeRight();

		void decodeFile(std::string& in_file, std::string& out_file);
		bool decodeFileRead(std::ifstream& encode_file, std::ofstream& original_file);
		void decodeFileWrite(std::ofstream& original_file);

		bool fileEof(std::ifstream& file);

		void debugShowKeyTable();
		void debugShowKeyTableRec(unit* start);
	};

}
