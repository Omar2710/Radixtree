#pragma once
#include "Node.h"
class Tree
{
private:
	Node* _root;
	int MatchingConsecutiveCharacters(string word, Node* curNode);
	void InsertRecursive(string wordPart, Node* curNode);
	bool LookupRecursive(string wordPart, Node* curNode);
	void DeleteRecursive(string wordPart, Node* curNode);
public:
	Tree();
	void Insert(string word);
	bool Lookup(string word);
	void Delete(string word);
};

