#pragma warning(disable : 4996)
#include <fstream>
#include <iostream>
#include <filesystem>
#include <cstring>
#include <stdio.h>
#include <time.h>

//#include "list.h"

using namespace std;
namespace fs = filesystem;

string convertToString(char* a) //преобразовать char в string
{
	string s = "";
	int size = sizeof(a) / sizeof(char);
	for (int i = 0; i < size; i++) {
		s = s + a[i];
	}
	return s;
}

struct dev_data {
	int sec;
	char dname[30] = { 0 };
	int data;
};

dev_data crusher(char trash[]) { // разделить строку в файле на sec, dname, data 
	dev_data clean;

	char* pch1 = strchr(trash, ':');
	char* pch2 = strchr(pch1 + 1, ':');
	char tmp[40];
	strncpy(tmp, trash, pch1 - trash);
	clean.sec = atoi(tmp);
	memset(tmp, 0, 40);
	strncpy(clean.dname, pch1 + 1, pch2 - pch1 - 1);
    strcpy(tmp, pch2 + 1);
	clean.data = atoi(tmp);

	return clean;
}

bool check_error(char trash[]) // поиск ненужных строк
{
	if (strlen(trash) == 0) return false; //если длинна строки равна нулю
	else if (strstr(trash, "garbage") == nullptr) return true;
	else return false;
}

string GetDayOfWeek(string new_date, int sec) //разделить имя файлам на год, месяс и тд.
{
	char date[50] = { 0 };
	new_date.copy(date, new_date.size());// из строки new_date в  date коприруем колличество символов
	date[new_date.size()] = '\0';


	time_t rawtime;
	struct tm* timeinfo; //Структура, содержащая календарную дату и время, разбитая на составляющиe
	time(&rawtime); // получить текущую дату, выраженную в секундах
	timeinfo = localtime(&rawtime);

	char* pch1 = strchr(date, '-'); // поиск символа '-' в строке date
	char* pch2 = strchr(pch1 + 1, '-');
	char* pch3 = strchr(pch2 + 1, ' ');
	char* pch4 = strchr(pch3 + 1, '-');
	char tmp[40];
	strncpy(tmp, date, 4); //в tmp копируем 4 символа из date
	timeinfo->tm_year = atoi(tmp) - 1900;
	memset(tmp, 0, 40); //обнулить tmp
	strncpy(tmp, pch1 + 1, 2);
	timeinfo->tm_mon = atoi(tmp) - 1;
	memset(tmp, 0, 40);
	strncpy(tmp, pch2 + 1, 2);
	timeinfo->tm_mday = atoi(tmp);
	memset(tmp, 0, 40);
	strncpy(tmp, pch3 + 1, 2);
	timeinfo->tm_hour = atoi(tmp);
	memset(tmp, 0, 40);
	strncpy(tmp, pch4 + 1, 2);
	timeinfo->tm_min = atoi(tmp);
	memset(tmp, 0, 40);
	timeinfo->tm_sec = sec;

	mktime(timeinfo);

	char buf[80] = { 0 };

	strftime(buf, 80, "%a %d %b %Y %T", timeinfo); //из timeinfo получить время
	//printf(buf);
	return string(buf);
}


string ExtractDateFromFileName(string name) //поместить имя файла в строку
{
	return name.substr(name.find("_(") + 2, 16);
}



void FileData(char tmp[]) {
	for (auto& p : fs::directory_iterator("logs")) {
		char S[30];
		ifstream pp(p.path());
		while (!pp.eof()) // читать информацию  до конца файла
		{
			pp.getline(S, 100); //Построчное считывание информации в S
			if (check_error(S)) {
				dev_data recycled = crusher(S);
				if (strcmp(recycled.dname, tmp) == 0) {
					cout << GetDayOfWeek(ExtractDateFromFileName(p.path().string()), recycled.sec)\
						<< " - " << recycled.data << "\n";
				}
			}
		}
		pp.close();

	}
}


void Menu() {
	while (true) {
		cout << "\nCommand list:\n";
		cout << "show device\n";
		cout << "show device <name>\n";
		cout << "exit\n";

		cout << ".>> ";
		char com[100] = { 0 };
		std::cin.getline(com, 100);

		if (strstr(com, "show device")) {
			
			char* pch1 = strrchr(com, ' ');
			char dname[40];
			strcpy(dname, pch1 + 1);
			cout << "\n           date" << "          - indications\n"<<endl;
			FileData(dname);
		}
		if (strstr(com, "exit")) {
			exit(0);
		}
	}


}

int main()
{
	if (!fs::exists("logs")) {
		std::cout << "directory logs does not exist\n";
		exit(0);
	}

	Menu();
	
}
