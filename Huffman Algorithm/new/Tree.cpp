#include "Tree.h"

Tree::Tree()
{
	_head = nullptr;
	_previous = nullptr;
}

Tree::~Tree()
{

}

void Tree::addToTree(const uint32_t& symbol_frequency, const char& symbol)
{
	if (headIsNull()) addToHead(symbol_frequency, symbol);
	else addToBranches(symbol_frequency, symbol);
}

bool Tree::headIsNull()
{
	if (_head == nullptr) return true;
	return false;
}

void Tree::addToHead(const uint32_t& symbol_frequency, const char& symbol)
{
	node* newSymbol = new node(symbol_frequency, symbol);
	_head = newSymbol;
}

void Tree::addToBranches(const uint32_t& symbol_frequency, const char& symbol)
{
	node* iterator = _head;
	while (iterator != nullptr) addToLeftOrRight(symbol_frequency, symbol, iterator);
	pushNode(symbol_frequency, symbol);
	delete iterator;
}

void Tree::addToLeftOrRight(const uint32_t& symbol_frequency, const char& symbol, node* iterator)
{
	_previous = iterator;
	if (symbol_frequency < iterator->_symbol_frequency) iterator = iterator->_left;
	else iterator = iterator->_right;
}

void Tree::pushNode(const uint32_t& symbol_frequency, const char& symbol)
{
	if (symbol_frequency < _previous->_symbol_frequency) pushNodeLeft(symbol_frequency, symbol);
	else pushNodeRight(symbol_frequency, symbol);
}

void Tree::pushNodeLeft(const uint32_t& symbol_frequency, const char& symbol)
{
	node* newSymbol = new node(symbol_frequency, symbol);
	_previous->_left = newSymbol;
}

void Tree::pushNodeRight(const uint32_t& symbol_frequency, const char& symbol)
{
	node* newSymbol = new node(symbol_frequency, symbol);
	_previous->_right = newSymbol;
}

void Tree::showTree()
{
	showMin(_head);
}

void Tree::showMin(const node* head)
{
	//if (head->_left != nullptr) showMin(head->_left);
	//std::cout << head->_symbol_frequency << " ";
	//if (head->_right != nullptr) showMin(head->_right);

}
