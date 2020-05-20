#include "ACrypt.h"

/*ACrypt::ACrypt()
{
    //ctor
}

ACrypt::~ACrypt()
{
    //dtor
}*/

void ACrypt::WriteKey(string name) {
	ofstream out(name);
	string tmp = this->key.dump();
	out << tmp << endl;
	out.close();
}

/////////////////////////////////////////////////////////////////////////////////////////
void ACrypt::WriteText(string name) {
	ofstream out(name);
	out << this->text.dump() << endl;
	out.close();
}
/////////////////////////////////////////////////////////////////////////////////////////
void ACrypt::WriteEncrypt(string name) {
	ofstream out(name);
	out << this->encrypt.dump() << endl;
	out.close();
	
}
/////////////////////////////////////////////////////////////////////////////////////////
bool ACrypt::GetKey(string name) {
	if (name.substr(name.find_last_of(".") + 1) == "key") {

		ifstream in(name);
		if (!in.fail()) {
			if (in.is_open())
			{
				json tmp;
				in >> tmp;
				if (tmp.size() == 2) {

					if (tmp.find("key") != tmp.end() and tmp.find("alg_type") != tmp.end()) {
						if (tmp["alg_type"] == this->algot){

							this->key = tmp;
							in.close();
							return true;
						} else cout << "������ ���� �� ������� ��������� ����������!\n";
					} else cout << "������ �������! �������� ���� ���������.\n";
				}
				else cout << "������ �������! �������� ���� ���������.\n";
				in.close();
			}
			else cout << "����� � ������ " << name << " �� ����������!\n";
		}
		else cout << "����� ���\n";
	}
	else cout << "������. ��������� ���� � ����������� *.key\n";
	return false;
}
/////////////////////////////////////////////////////////////////////////////////////////
bool ACrypt::GetText(string name) {
	if (name.substr(name.find_last_of(".") + 1) == "txt") {

		ifstream in(name);
		if (in.fail()) {
			cout << "file is not present\n";
			return false;
		}
		string file_contents{ istreambuf_iterator<char>(in), istreambuf_iterator<char>() };
		this->text = file_contents;
		in.close();
		return true;
	}
	else {
		cout << "file is not present\n";
		return false;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
bool ACrypt::GetEncrypt(string name) {
	if (name.substr(name.find_last_of(".") + 1) == "encrypt") {

		ifstream in(name);
		if (!in.fail()) {
			if (in.is_open())
			{
				json tmp;
				in >> tmp;
				if (tmp.size() == 2) {
					if (tmp.find("text") != tmp.end() and tmp.find("alg_type") != tmp.end()) {
						if (tmp["alg_type"] == this->algot) {
							this->encrypt = tmp;
							in.close();
							return true;
						}
						else cout << "������ ����� ��� ���������� ������ ���������� ����������. ����������� �� ���������!\n";
					}
					else cout << "������ �������! �������� ���� ���������.\n";
				}
				else cout << "������ �������! �������� ���� ���������.\n";
				in.close();
			}
			else cout << "����� � ������ " << name << " �� ����������!\n";
		}
		else cout << "����� ���\n";
	}
	else cout << "������. ��������� ���� � ����������� *.encrypt\n";
	return false;
}
/////////////////////////////////////////////////////////////////////////////////////////
bool ACrypt::GetAlphabet(string name) {
	if (name.substr(name.find_last_of(".") + 1) == "alph") {

		ifstream in(name);
		if (!in.fail()) {
			if (in.is_open())
			{
				json tmp;
				in >> tmp;
				if (tmp.size() == 1) {
					auto it = tmp.find("alp");
					if (it != tmp.end()) {
						this->alphabet = tmp;
						in.close();
						return true;
					}
				}
				else cout << "������ �������! �������� ���� ���������.";
				in.close();
			}
			else cout << "����� � ������ " << name << " �� ����������!";
		}
		else cout << "����� ���\n";
	}
	else cout << "������. ��������� ���� � ����������� *.alph\n";
	return false;
}
/////////////////////////////////////////////////////////////////////////////////////////

