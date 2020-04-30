#include<stdio.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <chrono>
//#include<math.h>
using namespace std;


class APA {
	//Arbitrary Precision Arithmetic
private:
	static const int dig_base = 9; // Количество хранимых разрядов
	static const int base = 1000000000; // основание

	vector<int> big_variable; // хранилище
	bool isneganum; // знак числа
	void remove_leading_zeros();
	void resize_vector(size_t n);

	friend APA mul2(const APA& first, const APA& second);
	friend bool compare_less_or_equal(const APA& first, const APA& second);

public:
	// класс-исключение, бросаемое при делении на ноль
	class divide_by_zero : public std::exception {  };
	class value_error : public std::exception {  };
	APA();
	APA(string sval);
	APA(signed int i);

	bool checkisdigit(string sval);
	void move_right();


	const APA operator +() const;
	const APA operator -() const;
	friend const APA operator +(APA first, const APA& second);
	friend const APA operator -(APA first, const APA& second);
	friend const APA operator *(APA first, APA second);
	friend const APA operator /(APA first, APA second);

	void print();
};
///////////////////////////////////////////////////////////////////////////////////////////////
APA::APA()
{
	this->isneganum = false;
	this->big_variable.push_back(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////
APA::APA(string sval)
{
	int offset = 0;
	if (sval.size() == 0)
	{
		this->isneganum = false;
		this->big_variable.push_back(0);
	}
	else {
		if (isdigit(sval[0]) == 0) {
			if (sval[0] == '-') this->isneganum = true;
			else this->isneganum = false;
			offset = 1;
		}
		else {
			this->isneganum = false;
		}
		int i = sval.size();
		do
		{
			if (i < dig_base) {
				if (!checkisdigit(sval.substr(offset).c_str())) {
					this->big_variable.clear();
					throw APA::value_error();
				}
				big_variable.push_back(atoi(sval.substr(offset).c_str()));
			}
			else
			{
				if (!checkisdigit(sval.substr(sval.size() - dig_base).c_str())) {
					this->big_variable.clear();
					throw APA::value_error();
				}
				big_variable.push_back(atoi(sval.substr(sval.size() - dig_base).c_str()));
				sval.erase(sval.size() - dig_base);

			}
			i = i - dig_base;
		} while (i > 0);

	}
	remove_leading_zeros();
}

APA::APA(signed int i) {
	if (i < 0) this->isneganum = true;
	else this->isneganum = false;
	this->big_variable.push_back(abs(i) % APA::base);
	i = i / APA::base;
	if (i != 0) this->big_variable.push_back(abs(i));
}

void APA::remove_leading_zeros()
{
	while (big_variable.back() == 0 and big_variable.size() > 1) big_variable.pop_back();
}
///////////////////////////////////////////////////////////////////////////////////////////////
bool APA::checkisdigit(string sval)
{
	size_t i = 0;
	do
	{
		if (!isdigit(sval[i])) return false;
		else i++;
	} while (i < sval.size());
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////
const APA APA::operator +() const {
	return APA(*this);
}
///////////////////////////////////////////////////////////////////////////////////////////////
const APA APA::operator -() const {
	APA new_value(*this);
	new_value.isneganum = !new_value.isneganum;
	return new_value;
}
///////////////////////////////////////////////////////////////////////////////////////////////
const APA operator +(APA first, const APA& second) {
	if (first.isneganum)
		if (second.isneganum) return -((-first) + (-second));
		else return second - (-first);
	else
		if (second.isneganum) return first - (-second);
		else if (first.big_variable.size() < second.big_variable.size()) return second + first;
	int carryover = 0;
	size_t i = 0;
	while (i < second.big_variable.size() or carryover == 1)
	{
		if (i == first.big_variable.size() and carryover == 1) first.big_variable.push_back(0);
		auto tmp = first.big_variable[i] + (i < second.big_variable.size() ? second.big_variable[i] : 0) + carryover;
		if (tmp >= APA::base)
		{
			tmp = tmp - APA::base;
			carryover = 1;
		}
		else carryover = 0;
		first.big_variable[i] = tmp;
		i++;
	}
	return first;
}
///////////////////////////////////////////////////////////////////////////////////////////////
const APA operator -(APA first, const APA& second) {
	if (first.isneganum)
		if (second.isneganum) return -((-second) + (-first));
		else return -((-first) + second);
	else if (second.isneganum) return first + (-second);

	if (first.big_variable.size() < second.big_variable.size()) return -(second - first);
	if (first.big_variable.size() == second.big_variable.size())
	{
		int j = first.big_variable.size() - 1;
		while (j >= 0)
		{
			if (first.big_variable[j] < second.big_variable[j]) return -(second - first);
			else if (first.big_variable[j] > second.big_variable[j]) break;
			j--;
		}
	}
	int carryover = 0;
	size_t i = 0;
	while (i < second.big_variable.size() or carryover == 1)
	{
		auto tmp = first.big_variable[i] - (i < second.big_variable.size() ? second.big_variable[i] : 0) - carryover;
		if (tmp < 0)
		{
			tmp = tmp + APA::base;
			carryover = 1;
		}
		else carryover = 0;
		first.big_variable[i] = tmp;
		i++;
	}
	first.remove_leading_zeros();
	return first;
}
///////////////////////////////////////////////////////////////////////////////////////////////
void APA::resize_vector(size_t n) {
	if (this->big_variable.size() >= n) return;
	else {
		while (this->big_variable.size() != n) {
			this->big_variable.push_back(0);
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////
APA mul2(const APA& first, const APA& second) {
	APA result;
	result.big_variable.resize(first.big_variable.size() + second.big_variable.size());
	size_t i = 0;
	while (i < first.big_variable.size()) {
		int carryover = 0;
		size_t j = 0;
		while (j < second.big_variable.size() or carryover != 0) {
			long long tmp = result.big_variable[i + j] +
				first.big_variable[i] * 1LL * (j < second.big_variable.size() ? second.big_variable[j] : 0) + carryover;
			result.big_variable[i + j] = static_cast<int>(tmp % APA::base);
			carryover = static_cast<int>(tmp / APA::base);
			j++;
		}
		i++;
	}

	result.isneganum = first.isneganum != second.isneganum;
	result.remove_leading_zeros();
	return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////
const APA operator *(APA first, APA second) {
	if (first.isneganum)
		if (second.isneganum) return (-first) * (-second);
		else return -((-first) * second);
	else if (second.isneganum) return -(first * (-second));

	size_t n = max(first.big_variable.size(), second.big_variable.size());
	if (n % 2 == 1) n++;

	first.resize_vector(n);
	second.resize_vector(n);

	APA result;
	result = mul2(first, second);

	result.remove_leading_zeros();
	return result;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void APA::move_right() {
	if (this->big_variable.size() == 0) {
		this->big_variable.push_back(0);
		return;
	}
	this->big_variable.push_back(this->big_variable[this->big_variable.size() - 1]);
	for (size_t i = this->big_variable.size() - 2; i > 0; --i) this->big_variable[i] = this->big_variable[i - 1];
	this->big_variable[0] = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
bool compare_less_or_equal(const APA& first, const APA& second) {
	if (first.big_variable.size() < second.big_variable.size()) return true;
	if (first.big_variable.size() == second.big_variable.size())
	{
		int j = first.big_variable.size() - 1;
		while (j >= 0)
		{
			if (first.big_variable[j] < second.big_variable[j]) return true;
			else if (first.big_variable[j] > second.big_variable[j]) return false;
			j--;
		}
		if (first.big_variable[0] == second.big_variable[0]) return true;
	}
	return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
const APA operator /(APA first, APA second) {
	if (second.big_variable.size() == 1 and second.big_variable[0] == 0) throw APA::divide_by_zero();
	APA b = second;
	b.isneganum = false;
	APA result, current;
	result.big_variable.resize(first.big_variable.size());
	for (int i = first.big_variable.size() - 1; i >= 0; --i) {
		current.move_right();
		current.big_variable[0] = first.big_variable[i];
		current.remove_leading_zeros();
		int x = 0, l = 0, r = APA::base;
		while (l <= r) {
			int m = (l + r) / 2;
			APA t;
			t = b * m;

			if (compare_less_or_equal(t, current)) {
				x = m;
				l = m + 1;
			}
			else r = m - 1;
		}

		result.big_variable[i] = x;
		current = current - b * x;
	}

	result.isneganum = first.isneganum != second.isneganum;
	result.remove_leading_zeros();
	return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////
void APA::print() {
	printf("\n");
	if (this->isneganum) printf("-");
	if (this->big_variable.size() == 1 and this->big_variable[0] == 0) {
		printf("0");
	}
	else {
		printf("%d", this->big_variable[this->big_variable.size() - 1]);
		if (!(this->big_variable.size() == 1)) {
			int i = this->big_variable.size() - 2;
			while (0 <= i) {
				printf("%09d", this->big_variable[i]);
				i--;
			}
		}
	}
	printf("\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////
void menu_operation(APA first, APA second, bool testmode) {

	cout << "Первое число:\n";
	first.print();
	cout << "Второе число:\n";
	second.print();


	bool nonexistop = false;
	char op = '0';
	while (op != 'q') {
		try {
			nonexistop = false;
			long int timetmp = 0;
			chrono::steady_clock::time_point timebegin;
			chrono::steady_clock::time_point timeend;
			cout << "\nВведите операцию ( +, -, *, /) или q(quit):\n";
			cin >> op;
			APA result;

			if (testmode) cout << "Processing";

			int i = 0;
			while (i < ((testmode) ? 1000 : 1)) {
				if (testmode) {
					timebegin = chrono::steady_clock::now();
					cout << ".";
				}
				switch (op) {
				case '+':
					result = first + second;
					break;
				case '-':
					result = first - second;
					break;
				case '*':
					result = first * second;
					break;
				case '/':
					result = first / second;
					break;
				case 'q':
					cout << "quit\n";
					break;
				default:
					cout << "Операции " << op << " не существует!\n";
					nonexistop = true;
					break;
				}
				if (testmode) {
					timeend = chrono::steady_clock::now();
					auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(timeend - timebegin);
					timetmp += static_cast<long int>(elapsed_ms.count());
				}
				i++;
				if (op == 'q' or nonexistop) break;
				if (!testmode or i == 999) result.print();
			}
			if (testmode) cout << "\nСреднее время выполнения операции равно " << timetmp / 1000.0 << " ms\n";
		}
		catch (const APA::divide_by_zero&) {
			cout << "Делить на ноль нельзя!\n";
			continue;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////
void menu_1() {
	string valtmp;
	int command = 0;
	bool testmode = false;

	while (command != 4) {
		cout << "Введите команду:\n" << "1)Ввести число\n" << "2)Взять число из файла\n" \
			<< "3)Enable test mode (current: ";
		if (testmode) cout << "enable)\n";
		else cout << "disable)\n";
		cout << "4)Выход\n";
		cin >> command;
		if (command == 1) {

			try {
				cout << "Введите первое число\n";
				cin >> valtmp;
				APA val1(valtmp);
				cout << "Введите второе число\n";
				cin >> valtmp;
				APA val2(valtmp);
				menu_operation(val1, val2, testmode);
			}
			catch (const APA::value_error&) {
				cout << "Значение содержит посторонний символ(ы)\n";
				continue;
			}
		}
		if (command == 2) {
			try {
				ifstream inf;
				string way;
				cout << "Введите путь файла для первого числа\n";
				cin >> way;

				inf.open(way);
				if (inf.fail()) {
					cout << "file is not present\n";
					inf.close();
					continue;
				}
				else getline(inf, valtmp, '\0');
				inf.close();

				APA val1(valtmp);

				cout << "Введите путь файла для второго числа\n";

				cin >> way;
				inf.open(way);

				if (inf.fail()) {
					cout << "file is not present\n";
					inf.close();
					continue;
				}
				else getline(inf, valtmp, '\0');
				inf.close();

				APA val2(valtmp);

				menu_operation(val1, val2, testmode);
			}
			catch (const APA::value_error&) {
				cout << "Значение содержит посторонний символ(ы)\n";
				continue;
			}
		}
		if (command == 3) {
			testmode = !testmode;
		}
	}
}

int main() {

	setlocale(LC_ALL, "Russian");

	menu_1();


}

