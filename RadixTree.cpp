// Tries-DataStructures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Tree.h"
using namespace std;


string CheckWord(Tree* tree, string word) {
	string message = "";
	if (tree->Lookup(word)) {
		message = word + " FOUND";
	}
	else {
		message = word + " NOT FOUND";
	}
	return message;
}

int main()
{
	Tree* tree = new Tree();
	tree->Insert("star");
	tree->Insert("Steve");
	tree->Insert("Stranza");

	cout << CheckWord(tree, "Steve") << endl;

	tree->Delete("Steve");

	cout << CheckWord(tree, "star") << endl;
	cout << CheckWord(tree, "Steve") << endl;
	cout << CheckWord(tree, "Stranza") << endl;
}


