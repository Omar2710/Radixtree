#include "Node.h"
#include <vector>
using namespace std;

Node::Node() {
	Word = "";
	SubNodes.clear();
}

Node::Node(string x)
{
	Word = x;
	SubNodes.clear();
}

vector<Node*>::iterator Node::GetIndex(Node* element) {
    return find(SubNodes.begin(), SubNodes.end(), element);
}

