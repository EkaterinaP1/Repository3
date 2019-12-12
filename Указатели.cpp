#include <iostream>
using namespace std;

void func( int pointerArr[5])
{
	for (int i = 0; i < 5; i++)

	{
		cout << pointerArr[i];
	}
}

void func2(int* pa) {
	(*pa) = 4;
}



int main(int* pa)
{
	int arr[5];
	int* pointerArr = arr;
	int a = 1;

	func2(&a);

	for (int i = 0; i < 5; i++)
    {
      arr[i] = a;
    }
	
	func(pointerArr);
}