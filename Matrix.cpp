#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
int main()
{
	ofstream myfile;
	myfile.open("example.txt");
	int command;
	cout << "Enter command" << endl << "1-static" << endl << "2-dinamic" << endl << "3-vector" << endl;
	cin >> command;
	cout << endl;
	switch (command) {
	case 1:
	{

		// Статический массив////////////////////////////////////////////////////////////////////////////////////////////////////\

		const int rows1 = 2;
		const int cols1 = 3;
		int arr1[rows1][cols1];
		for (int i = 0; i < rows1; i++) {

			for (int j = 0; j < cols1; j++) {
				arr1[i][j] = 4;
				std::cout << arr1[i][j];
			}

			std::cout << std::endl;
		}

		cout << endl;
		//system("pause");
		cout << endl;


		const int rows2 = 3;
		const int cols2 = 2;
		int arr2[rows2][cols2];
		for (int i = 0; i < rows2; i++) {

			for (int j = 0; j < cols2; j++) {
				arr2[i][j] = 5;
				std::cout << arr2[i][j];
			}

			std::cout << std::endl;
		}

		cout << endl;
		//system("pause");
		cout << endl;

		int arr3[rows1][cols2];
		for (int i = 0; i < rows1; i++) {

			for (int j = 0; j < cols2; j++) {
				arr3[i][j] = 0;
				for (int k = 0; k < cols1; k++) {

					arr3[i][j] += arr1[i][k] * arr2[k][j];

				}
			}

		}

		myfile << "Результат первой матрицы:" << endl;
		for (int i = 0; i < rows1; i++) {

			for (int j = 0; j < cols2; j++) {
				std::cout << arr3[i][j] << "\t";
				myfile << arr3[i][j] << "\t";

			}
			cout << endl;
		}
	}


	myfile << "\n";

	int command2;
	cout << endl << "enter 1 if you want to continue and 2 if you do not want" << endl;
	cin >> command2;
	if (command2 == 1) {
		cout << endl << "Enter command" << endl << "1-static" << endl << "2-dinamic" << endl << "3-vector";
		cin >> command;
	}

	if (command2 == 2) {
		break;
	}




	case 2:

		//Динамический массив////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		int rows1 = 2;
		int cols1 = 3;
		int** arr1 = new int* [rows1];
		for (int i = 0; i < rows1; i++) {
			arr1[i] = new int[cols1];

		}

		for (int i = 0; i < rows1; i++) {

			for (int j = 0; j < cols1; j++) {
				arr1[i][j] = 4;

			}
		}

		for (int i = 0; i < rows1; i++) {

			for (int j = 0; j < cols1; j++) {
				std::cout << arr1[i][j] << "\t";

			}
			cout << endl;

		}

		cout << endl;
		//system("pause");
		cout << endl;

		int rows2 = 3;
		int cols2 = 2;
		int** arr2 = new int* [rows2];
		for (int i = 0; i < rows2; i++) {
			arr2[i] = new int[cols2];

		}

		for (int i = 0; i < rows2; i++) {

			for (int j = 0; j < cols2; j++) {
				arr2[i][j] = 5;

			}
		}

		for (int i = 0; i < rows2; i++) {

			for (int j = 0; j < cols2; j++) {
				std::cout << arr2[i][j] << "\t";

			}
			cout << endl;
		}


		cout << endl;
		//system("pause");
		cout << endl;

		int** arr3 = new int* [rows1];
		for (int i = 0; i < rows1; i++) {
			arr3[i] = new int[cols2];

		}

		for (int i = 0; i < rows1; i++) {

			for (int j = 0; j < cols2; j++) {
				arr3[i][j] = 0;

				for (int k = 0; k < cols1; k++) {

					arr3[i][j] += arr1[i][k] * arr2[k][j];

				}
			}

		}

		myfile << "Результат второй матрицы:" << endl;
		for (int i = 0; i < rows1; i++) {

			for (int j = 0; j < cols2; j++) {
				std::cout << arr3[i][j] << "\t";
				myfile << arr3[i][j] << "\t";
			}
			cout << endl;

		}


		for (int i = 0; i < rows1; i++) {
			delete[] arr1[i];

		}
		delete[] arr1;

		for (int i = 0; i < rows2; i++) {
			delete[] arr2[i];

		}
		delete[] arr2;

		for (int i = 0; i < rows1; i++) {
			delete[] arr3[i];

		}
		delete[] arr3;

	}


	myfile << "\n";
	cout << endl << "enter 1 if you want to continue and 2 if you do not want" << endl;
	cin >> command2;
	if (command2 == 1) {
		cout << endl << "Enter command" << endl << "1-static" << endl << "2-dinamic" << endl << "3-vector" << endl;
		cin >> command;
	}

	if (command2 == 2) {
		break;
	}


	case 3:

		// Векторный массив////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		int rows1 = 2;
		int cols1 = 3;
		vector< vector<int> >arr1(rows1);
		for (int i = 0; i < rows1; i++) {
			arr1[i].resize(cols1);
			for (int j = 0; j < cols1; j++) {
				arr1[i][j] = 4;
				cout << arr1[i][j] << " ";
			}
			cout << '\n';
		}
		cout << endl;

		//system("pause");
		cout << endl;

		const int rows2 = 3;
		const int cols2 = 2;
		vector<vector<int> > arr2(rows2);

		for (int i = 0; i < rows2; i++) {
			arr2[i].resize(cols2);
			for (int j = 0; j < cols2; j++) {
				arr2[i][j] = 5;
				cout << arr2[i][j] << " ";
			}
			cout << '\n';
		}
		cout << endl;


		//system("pause");
		cout << endl;



		int rows3 = rows1;
		int cols3 = cols2;
		vector<vector<int> > arr3(rows3);
		myfile << "Результат третьей матрицы:" << endl;
		for (int i = 0; i < rows3; i++) {
			arr3[i].resize(cols3);
			for (int j = 0; j < cols3; j++) {
				arr3[i][j] = 0;
				for (int k = 0; k < cols1; k++) {
					arr3[i][j] += arr1[i][k] * arr2[k][j];
				}
				cout << arr3[i][j] << " ";
				myfile << arr3[i][j] << "\t";
			}
			cout << '\n';
		}
		cout << endl;
		//system("pause");
		cout << endl;

	}


	cout << endl << "enter 1 if you want to continue and 2 if you do not want" << endl;
	cin >> command2;
	if (command2 == 1) {
		cout << endl << "Enter command" << endl << "1-static" << endl << "2-dinamic" << endl << "3-vector" << endl;
		cin >> command;
	}

	if (command2 == 2) {
		break;
	}

	}


	myfile.close();


}


