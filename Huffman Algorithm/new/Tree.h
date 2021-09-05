#pragma once
#include <iostream>

// TODO: ��������, ����� �� ��� ����� ������ ��������

class Tree
{
public:
	Tree();
	~Tree();
	void addToTree(const uint32_t& symbol_frequency, const char& symbol);
private:
	struct node
	{
		node() {}
		node(uint32_t symbol_frequency, char symbol) : _symbol_frequency(symbol_frequency), _symbol(symbol) {}
		uint32_t _symbol_frequency = 0;
		char _symbol = '0';
		node* _left = nullptr, * _right = nullptr;
	};
	node* _head, * _previous;
	bool headIsNull();
	void addToHead(const uint32_t& symbol_frequency, const char& symbol);
	void addToBranches(const uint32_t& symbol_frequency, const char& symbol);
	void addToLeftOrRight(const uint32_t& symbol_frequency, const char& symbol, node* iterator);
	void pushNode(const uint32_t& symbol_frequency, const char& symbol);
	void pushNodeLeft(const uint32_t& symbol_frequency, const char& symbol);
	void pushNodeRight(const uint32_t& symbol_frequency, const char& symbol);

	void showTree();
	void showMin(const node* head);
};

