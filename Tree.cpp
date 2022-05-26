#include "Tree.h"
#include <iostream>

Tree::Tree() {
	_root = new Node();
}

int Tree::MatchingConsecutiveCharacters(string word, Node* curNode) {
	int matches = 0;
	int minLength = 0;
	//see which string is smaller and save it's length
	//when cycling throughut the two strings we won't go any further than that
	if (curNode->Word.length() >= word.length()) {
		minLength = word.length();
	}
	else if (curNode->Word.length() < word.length()) {
		minLength = curNode->Word.length();
	}

	//Check if the minLegth has any (Not empty string)
	if (minLength > 0) {
		//Go through the two words and find matching
		//1) Current Node's word
		//2) New entered word
		for (int i = 0; i < minLength; i++) {
			//if two chars at the same position are equal then we have one more match
			if (word[i] == curNode->Word[i]) {
				matches++;
			}
			else {
				//If at any position we don't find a match then the words are charachters are different
				break;
			}
		}
	}
	return matches;
}

void Tree::Insert(string word) {
	InsertRecursive(word, _root);
}

bool Tree::Lookup(string word) {
	return LookupRecursive(word, _root);
}

void Tree::Delete(string word) {
	DeleteRecursive(word, _root);
}

void Tree::InsertRecursive(string wordPart, Node* curNode) {

	//Get matching characters between current node and entered word
	int matches = MatchingConsecutiveCharacters(wordPart, curNode);

	if (matches == 0 || curNode == _root || (matches > 0 && matches < wordPart.length() && matches >= curNode->Word.length())) {
		bool inserted = false;
		//Remove the current node's word matching characters from the word part that is needed to be entered
		string unMatchingWordPart = wordPart.substr(matches, wordPart.length() - matches);
		//Search (Recursively) the curNode's subnodes if the subnode's word has any first characters that also match,
		for (Node* child : curNode->SubNodes) {
			if (child->Word[0] == unMatchingWordPart[0]) {
				inserted = true;
				InsertRecursive(unMatchingWordPart, child);
			}
		}
		//Create new child node if we reached the end
		if (!inserted) {
			curNode->SubNodes.push_back(new Node(unMatchingWordPart));
		}
	}
	else if (matches < wordPart.length()) {
		//We have 2 nodes we must add to the tree
		//1) node with word extracted from current node's word without the string on matching characters
		//2) node that has it's word extracted from the current word minus the string of matching characters
		string commonRoot = wordPart.substr(0, matches);
		string branchPreviousWord = curNode->Word.substr(matches, curNode->Word.length() - matches);
		string branchNewWord = wordPart.substr(matches, wordPart.length() - matches);

		curNode->Word = commonRoot;

		Node* newNodePreviousWord = new Node(branchPreviousWord);
		for (Node* prevSubNode : newNodePreviousWord->SubNodes) {
			newNodePreviousWord->SubNodes.push_back(prevSubNode);
		}

		curNode->SubNodes.clear();
		curNode->SubNodes.push_back(newNodePreviousWord);

		Node* newNodeNewWord = new Node(branchNewWord);
		curNode->SubNodes.push_back(newNodeNewWord);
	}
	else if (matches > curNode->Word.length()) {
		//The word entered is less than the curNode word.
		//Add the current word part minus the common characters after the current node
		string newNodeWord = curNode->Word.substr(curNode->Word.length(), wordPart.length());
		Node* newNode = new Node(newNodeWord);
		curNode->SubNodes.push_back(newNode);
	}
}

bool Tree::LookupRecursive(string wordPart, Node* curNode) {
	int matches = MatchingConsecutiveCharacters(wordPart, curNode);
	if (matches == 0 || curNode == _root || (matches > 0 && matches < wordPart.length() && matches >= curNode->Word.length())) {
		string unMatchingWordPart = wordPart.substr(matches, wordPart.length() - matches);
		for (Node* child : curNode->SubNodes) {
			if (child->Word[0] == unMatchingWordPart[0]) {
				return LookupRecursive(unMatchingWordPart, child);
			}
		}
		return false;
	}
	else if (matches == curNode->Word.length()) {
		return true;
	}
	else {
		return false;
	}
}

void Tree::DeleteRecursive(string wordPart, Node* curNode) {
	int matches = MatchingConsecutiveCharacters(wordPart, curNode);

	if (matches == 0 || curNode == _root || (matches > 0 && matches < wordPart.length() && matches >= curNode->Word.length())) {
		string unMatchingWordPart = wordPart.substr(matches, wordPart.length() - matches);
		for (Node* child : curNode->SubNodes) {
			if (child->Word[0] == unMatchingWordPart[0]) {
				if (unMatchingWordPart == child->Word) {
					//Only delte the child node if it doesn't have any subNodes
					if (child->SubNodes.empty()) {
						curNode->SubNodes.erase(curNode->GetIndex(child)); //Remove from subNodes
						return;
					}
				}

				DeleteRecursive(wordPart, child);
			}
		}
	}


}