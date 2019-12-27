#include <iostream> 
#include <string> 
#include <fstream> 
#include "list.h" 

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	tree my_tree_1;
	my_tree_1.add_elem(10);
	my_tree_1.add_elem(5);
	my_tree_1.add_elem(15);
	my_tree_1.add_elem(13);
	my_tree_1.add_elem(17);
	my_tree_1.add_elem(2);
	my_tree_1.add_elem(1);
	my_tree_1.add_elem(3);
	my_tree_1.add_elem(4);
	my_tree_1.add_elem(7);
	my_tree_1.add_elem(6);
	my_tree_1.add_elem(7);
	my_tree_1.add_elem(8);

	printf("Tree #######################");
	my_tree_1.tprint();

	printf("remove 2 #######################");
	my_tree_1.remove(5);
	my_tree_1.tprint();

	printf("remove all #######################");
	if (!my_tree_1.remove_all()) printf("Tree is empty!\n");
	my_tree_1.tprint();

	printf("#######################");

	return 0;
}
