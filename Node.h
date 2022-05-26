#pragma once
#include <string>
#include <vector>

using namespace std;
class Node
{
public:
	Node();
	Node(string x);
	string Word;
	vector<Node*> SubNodes;
	vector<Node*>::iterator GetIndex(Node* element);
};

