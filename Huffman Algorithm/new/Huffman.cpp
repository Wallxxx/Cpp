#include "Huffman.h"

namespace algorithms
{

	Huffman::Huffman()
	{
		root = nullptr;
		_all_symbols = _various_symbols = 0;
		_encode_value = _bits = 0;
	}

	Huffman::~Huffman()
	{
		_frequency.clear();
		_summary_table.clear();
		_frequency_table.clear();
		_way.clear();
	}

	Huffman::unit::unit()
	{
		_symbol_frequency = 0;
		_symbol = '\0';
		_left = _right = nullptr;
	}

	Huffman::unit::unit(char symbol, uint32_t symbol_frequency)
	{
		_symbol_frequency = symbol_frequency;
		_symbol = symbol;
		_left = _right = nullptr;
	}

	Huffman::unit::unit(unit* left, unit* right)
	{
		_left = left;
		_right = right;
		_symbol_frequency = left->_symbol_frequency + right->_symbol_frequency;
		_symbol = '\0';
	}

	Huffman::unit::~unit()
	{
		delete _left;
		delete _right;
	}

	void Huffman::encode(std::string& in_file, std::string& out_file)
	{
		stringHandlerOpenStreamRead(in_file);
		makeTable();
		saveKey();
		stringHandlerOpenStreamWrite(in_file, out_file);
	}

	void Huffman::stringHandlerOpenStreamRead(std::string& in_file)
	{
		std::ifstream stream(in_file);
		stringHandlerReader(stream);
		stream.close();
	}

	void Huffman::stringHandlerReader(std::ifstream& in_stream)
	{
		std::string line_from_file;
		while (getline(in_stream, line_from_file))
		{
			stringHandlerFilling(line_from_file);
		}
	}

	void Huffman::stringHandlerFilling(std::string& line_from_file)
	{
		for (const auto letter : line_from_file)
		{
			_frequency[letter] += 1;
			_all_symbols += 1;
			if (_frequency[letter] == 1) _various_symbols += 1;
		}
	}

	void Huffman::stringHandlerOpenStreamWrite(std::string& in_file, std::string& out_file)
	{
		std::ofstream out(out_file);
		std::ifstream in(in_file);
		stringHandlerReader(in, out);
		out.close();
		in.close();
	}

	void Huffman::stringHandlerReader(std::ifstream& in_stream, std::ofstream& out_stream)
	{
		std::string line_from_file;

		while (getline(in_stream, line_from_file))
		{
			for (const auto letter : line_from_file) stringHandlerReaderEncode(out_stream, letter);
		}
	}

	void Huffman::stringHandlerReaderEncode(std::ofstream& out_file, const char letter)
	{
		for (const auto code : _summary_table[letter])
		{
			_encode_value |= code << (7 - _bits++);
			if (_bits == 8) stringHandlerReaderEncodeWrite(out_file);
		}
	}

	void Huffman::stringHandlerReaderEncodeWrite(std::ofstream& out_file)
	{
		out_file << _encode_value;
		_bits = _encode_value = 0;
	}

	void Huffman::makeTable()
	{
		for (const auto& i : _frequency)
		{
			unit* temp = new unit(i.first, i.second);
			_frequency_table.push_back(temp);
		}
		makeTableTree();
	}

	void Huffman::makeTableTree()
	{
		while (_frequency_table.size() > 1)
		{
			_frequency_table.sort(compare());
			unit* head = new unit(makeTableTreeNodes(), makeTableTreeNodes());
			_frequency_table.push_back(head);
		}
		root = _frequency_table.front();
		makeWay(root);
	}

	Huffman::unit* Huffman::makeTableTreeNodes()
	{
		unit* node = new unit();
		node = _frequency_table.front();
		_frequency_table.pop_front();
		return node;
	}

	void Huffman::makeWay(unit* start)
	{
		if (start->_left != nullptr) { _way.push_back(false); makeWay(start->_left); }
		if (start->_right != nullptr) { _way.push_back(true); makeWay(start->_right); }
		if (start->_left == nullptr && start->_right == nullptr) 
			_summary_table[start->_symbol] = _way;
		if (_way.size() == 0) return;
		_way.pop_back();
	}

	void Huffman::saveKey()
	{
		std::ofstream key_file("key.txt");
		saveKeyAllSymbolsAmount(key_file, _all_symbols);
		saveKeyAllSymbolsAmount(key_file, _various_symbols);
		saveKeyAllSymbols(key_file);
		key_file.close();
	}

	void Huffman::saveKeyAllSymbolsAmount(std::ofstream& key_file, uint32_t amount)
	{
		while (amount > 0)
		{
			key_file << amount % 10;
			amount /= 10;
		}
		key_file << static_cast<char>(127);
	}

	void Huffman::saveKeyAllSymbols(std::ofstream& key_file)
	{
		for (const auto& symbol : _summary_table)
		{
			key_file << symbol.first;
			for (const auto& code : symbol.second) key_file << code;
			key_file << static_cast<char>(127);
		}
	}
}
