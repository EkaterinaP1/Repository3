#pragma once 
#include <string> 
using namespace std;
class tree_elem
{
public:
	int key;
	tree_elem* left;
	tree_elem* right;
	tree_elem* parent;

	tree_elem(int key, tree_elem* parent, tree_elem* left, tree_elem* right);


};


class tree {
private:
	tree_elem* head;
	tree_elem* _find(int key);
	void _tprint(tree_elem* el, int l);
public:

	tree();
	
	void add_tree(int key);
	bool add_elem(int key);
	bool remove(int key);
	tree_elem* min_elem(tree_elem* elem);
	tree_elem* max_elem(tree_elem* elem);
	bool remove_all();
	void find(tree_elem* elem, int key);
	void tprint();


};