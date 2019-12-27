#include "list.h" 
#include <ostream> 
#include <iostream> 
#include <math.h> 

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
tree_elem::tree_elem(int key = 0, tree_elem* parent = nullptr, tree_elem* left = nullptr, tree_elem* right = nullptr) {

	this->key = key;
	this->parent = parent;
	this->right = right;
	this->left = left;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
tree::tree() {
	this->head = nullptr;

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// создает структуру дерева
void tree::add_tree(int key) {

	tree_elem* new_elem = new tree_elem(key); //выделение памяти под корень дерева

	this->head = new_elem;

	return;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
tree_elem* tree::_find(int key) {
	auto iterator = this->head; // указатель на начало дерева
	while (iterator != nullptr)   // пока есть элементы
	{
		if (key == iterator->key) {  // если искомое значение равно элементу дерева
			return iterator;
		}
		if (key < iterator->key)      //если искомое значение меньше элемента дерева
			iterator = iterator->left;  // переходим в влево
		else
			iterator = iterator->right; // иначе вправо
	}
	return iterator;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool tree::add_elem(int key) {

	if (this->head == nullptr) { //если дерева не существует выполняем функцию add_tree
		add_tree(key);
		return true;
	}
	tree_elem* new_elem = new tree_elem(key);
	/* Поиск нужной позиции для вставки */
	auto iterator = this->head;
	while (iterator != nullptr)  //пока в начале есть элемент
	{
		if (key == iterator->key) {  //если индекс равен key;
			return false;
		}
		if (key < iterator->key) //если элемент меньше начального элемента
			if (iterator->left != nullptr)    // если в левом поддереве есть значение
				iterator = iterator->left;   // переходим на следующий влево
			else {
				iterator->left = new_elem;  // иначе создаем новый элемент
				new_elem->parent = iterator;   //
			}
		else
			if (iterator->right != nullptr)   //  
				iterator = iterator->right;   //
			else {
				iterator->right = new_elem;   //
				new_elem->parent = iterator;   //
			}
	}
	return true;   //
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool tree::remove(int key) {     //сделать проверку на начальный элемент head

	if (this->head == nullptr)
	{
		printf("Head is NULL!");
		return false;
	}

	auto removed_elem = this->_find(key);   //найти элемент

	if (removed_elem == nullptr) {   //если элемента нет - нечего удалять
		return false;
	}
	auto removed_elem_parent = removed_elem->parent;   // указатель на parent
	auto removed_elem_left = removed_elem->left;  //указатель на left дочерний эл-т
	auto removed_elem_right = removed_elem->right;  //указатель на right дочерний эл-т

	if (removed_elem_parent->left == removed_elem) {  // если левый родительский эл-т равен rem эл-ту
		// исправить указатель родительского левого эл-та на левый дочерний эл-т, удаляемого эл-та 
		removed_elem_parent->left = removed_elem_left;
		// исправить указатель на родителя для левого дочернего эл-та
		auto min_left = this->min_elem(removed_elem_left); 
		min_left->right = removed_elem_right;  // 
		removed_elem_right->parent = min_left;  // //исправить указатель на родителя для правого дочернего элемента
	}
	else if (removed_elem_parent->right == removed_elem) {//
		removed_elem_parent->right = removed_elem_right; //
		removed_elem_right->parent = removed_elem_parent;  //
		auto max_right = this->min_elem(removed_elem_right); //
		max_right->left = removed_elem_left;  // 
		removed_elem_left->parent = max_right;  //
	}
	delete removed_elem;

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void tree::find(tree_elem* elem, int key) {

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Минимальный элемент дерева
tree_elem* tree::min_elem(tree_elem* elem)
{
	auto min_elem = elem;
	while (min_elem->left != nullptr)
		min_elem = min_elem->left;
	return min_elem;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Максимальный элемент дерева
tree_elem* tree::max_elem(tree_elem* elem)
{
	auto max_elem = elem;
	while (max_elem->right != nullptr)
		max_elem = max_elem->right;
	return max_elem;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool tree::remove_all() {

	if (this->head == nullptr)
	{
		printf("Head is NULL! Tree is empty! \n");
		return false;
	}

	auto el = this->head->left;
	tree_elem* tmp = nullptr;
	int i = 0;
	while (el != nullptr) {
		i++;
		//printf("i = %d, k = %d\n", i, el->key);
		if (el->left != nullptr) {
			el = el->left;
		}
		else if (el->right != nullptr) {
			el = el->right;
		}
		else {

			if (el->parent != nullptr) {
				tmp = el;
				el = el->parent;
			}
			else {
				//printf("%d\n",el->key);
				delete el;
			}
			if (el->left == tmp) {
				el->left = nullptr;
			}
			if (el->right == tmp) {
				el->right = nullptr;
			}
			//printf("%d\n",tmp->key);
			delete tmp;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tree::tprint() {
	_tprint(this->head, 0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tree::_tprint(tree_elem* el, int l) {
	char symb = ' ';
	if (el == nullptr) {
		return;
	}
	else
	{
		for (int i = 0; i < l; i++)
		{
			printf("|    ");
		}
		printf("\n");
		for (int i = 1; i <= l - 1; i++)
		{
			printf("|    ");
		}
		if (l != 0) {
			printf("|--->");
		}
		printf("%d\n", el->key);
		_tprint(el->right, l + 1);
	}
	_tprint(el->left, l + 1);
}