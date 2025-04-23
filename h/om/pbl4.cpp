/*
============================================================================
Name        : pbl4.cpp
Author      : Om
Subject     : Project Based Learning
Description : AVL Trees
============================================================================
*/

#include <iostream>

using namespace std;

int max(int,int);

class AVL_Node {
	public:
		string word;
		string meaning;
		AVL_Node *left;
		AVL_Node *right;
		friend class AVL_Tree;
};

class AVL_Tree {

	public:

		AVL_Node *root;

		int height(AVL_Node*);
		int diff(AVL_Node*);
		AVL_Node *RR_Rotation(AVL_Node*);
		AVL_Node *LL_Rotation(AVL_Node*);
		AVL_Node *LR_Rotation(AVL_Node*);
		AVL_Node *RL_Rotation(AVL_Node*);
		AVL_Node *balance(AVL_Node*);
		void insert();
		AVL_Node *insert(AVL_Node*, AVL_Node*);
		void display(AVL_Node*);
		AVL_Node *search(AVL_Node*, AVL_Node *);
		void update();

		AVL_Tree();
};

int main() {

	AVL_Tree avl;

	int choice;
	do {
		cout << "Please Select the Action you wish to perform:" << endl
				<< "1. Insert" << endl
				<< "2. Display" << endl
				<< "3. Search a Word" << endl
				<< "4. Update the Meaning of a Word" << endl
				<< "5. EXIT" << endl
				<< "Enter your Choice: ";
		cin >> choice;

		AVL_Node *srch;
		AVL_Node *wrd;
		switch(choice) {

			case 1:
				avl.insert();
				break;

			case 2:
				avl.display(avl.root);
				break;

			case 3:
				cout << endl << "Enter the word to display:";
				wrd = new AVL_Node;
				cin >> wrd -> word;

				srch = avl.search(wrd, avl.root);

				if (srch == 0) {
					cout << endl << "Word Not Found" << endl;
				}
				else {
					cout << endl << "Word: " << srch -> word << endl;
					cout << "Meaning: " << srch -> meaning << endl << endl;
				}

				break;

			case 4:
				avl.update();
				break;

			case 5:
				break;

			default:
				cout << endl << "Please enter correct inputs" << endl;
		}
	}while(choice != 5);
	return 0;
}

AVL_Tree::AVL_Tree() {
	root = NULL;
}

int max(int a, int b) {

	if(a > b) {
		return a;
	}
	else {
		return b;
	}
}

int AVL_Tree::diff(AVL_Node *temp) {

	int lHeight = height(temp -> left);
	int rHeight = height(temp -> right);
	int bFactor = lHeight - rHeight;
	return bFactor;
}

int AVL_Tree::height(AVL_Node *temp) {

	int h = 0;
	if(temp != NULL) {
		int lHeight = height(temp -> left);
		int rHeight = height(temp -> right);
		int maxHeight = max(lHeight,rHeight);
		h = maxHeight + 1;
	}
	return h;
}

AVL_Node *AVL_Tree::RR_Rotation(AVL_Node *parent) {

	AVL_Node *temp = parent -> right;
	parent -> right = temp -> left;
	temp -> left = parent;
	return temp;
}

AVL_Node *AVL_Tree::LL_Rotation(AVL_Node *parent) {

	AVL_Node *temp = parent -> left;
	parent -> left = temp -> right;
	temp -> right = parent;
	return temp;
}

AVL_Node *AVL_Tree::LR_Rotation(AVL_Node *parent) {

	AVL_Node *temp = parent -> left;
	parent -> left = RR_Rotation(temp);
	return LL_Rotation(parent);
}

AVL_Node *AVL_Tree::RL_Rotation(AVL_Node *parent) {

	AVL_Node *temp = parent -> right;
	parent -> right = LL_Rotation(temp);
	return RR_Rotation(parent);
}

AVL_Node *AVL_Tree::balance(AVL_Node *temp) {

	int balFactor = diff(temp);

	if(balFactor > 1) {
		if(diff(temp -> left) > 0) {
			cout << endl << "Performing LL Rotation:" << endl;
			temp = LL_Rotation(temp);
			cout << endl;
		}
		else {
			cout << endl << "Performing LR Rotation:" << endl;
			temp = LR_Rotation(temp);
			cout << endl;
		}
	}

	else if(balFactor < -1) {
		if(diff(temp -> right) > 0) {
			cout << endl << "Performing RL Rotation:" << endl;
			temp = RL_Rotation(temp);
			cout << endl;
		}
		else {
			cout << endl << "Performing RR Rotation:" << endl;
			temp = RR_Rotation(temp);
			cout << endl;
		}
	}
	return temp;
}

void AVL_Tree::insert() {

	char ch;
	do {
		AVL_Node *temp;
		temp = new AVL_Node;
		cout << endl << "Enter the Word:";
		cin >> temp -> word;
		cout << "Enter it's Meaning:";
		cin >> temp -> meaning;
		root = insert(root,temp);
		display(root);
		cout << endl << "Enter 'y' to add another word:";
		cin >> ch;
	}while(ch == 'y');
}

AVL_Node *AVL_Tree::insert(AVL_Node *root, AVL_Node *temp) {

	if(root == NULL) {
		root = new AVL_Node;
		root -> word = temp -> word;
		root -> meaning = temp -> meaning;
		root -> left = NULL;
		root -> right = NULL;
		return root;
	}

	else if(temp -> word < root -> word) {
		root -> left = insert(root -> left, temp);
		root = balance(root);
	}

	else if(temp -> word >= root -> word) {
		root -> right = insert(root -> right, temp);
		root = balance(root);
	}

	return root;
}

void AVL_Tree::display(AVL_Node *rt) {

	cout << endl << "Word:" << rt ->word << endl;
	cout << "Meaning:" << rt -> meaning << endl << endl;

	if(rt -> left != NULL) {
		display(rt -> left);
	}

	if(rt -> right != NULL) {
		display(rt -> right);
	}
}

AVL_Node *AVL_Tree::search(AVL_Node *rt, AVL_Node *r) {

	if(r != NULL) {
		if(r -> word == rt -> word) {
			return r;
		}
		else if(rt -> word < r -> word) {
			return search(rt, r -> left);
		}
		else if(rt -> word > r -> word) {
			return search(rt, r -> right);
		}
	}

	return 0;
}

void AVL_Tree::update(){

	AVL_Node *temp;
	temp = new AVL_Node;

	cout << endl << "Enter the word whose meaning is to be changed:";
	cin >> temp -> word;

	temp = search(temp, root);

	if (temp == 0) {
		cout << endl << "Word not found" << endl;
	}
	else {
		cout << "Enter the new meaning of the word:";
		cin >> temp -> meaning;
		cout << endl;
	}
}
