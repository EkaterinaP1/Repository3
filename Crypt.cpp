
#include <stdio.h>
#include <iomanip>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "CryptChange.h"
#include "CryptShift.h"
#include "CryptGamma.h"

using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////
void menu() {
	int s_key;
	string text, crypt_text, key, alphabet;
	ACrypt* Encryption;
	int com;
	cout << "Главное меню\n" << "1) Зашифровать/Расшифровать\n" << "2) Сгенерировать ключ\n" << endl;
	cin >> com; cout << endl;

	if (com == 1) {
		com = 0;
		cout << "1) Зашифровать\n" << "2) Расшифровать\n" << endl;

		cin >> com;

		if (com == 1) {
			com = 0;
			cout << "Выберите метод шифровки:\n" << "1) Применить шифр заменой\n" << "2)  Применить шифр перестановкой\n" << "3)  Применить шифр гаммирования \n" << endl;
			cin >> com; cout << endl;
			if (com == 1) {
				cout << "Укажите файл с текстом:(.txt) :"; cin >> text; cout << endl;
				cout << "Укажите файл куда запишиться зашифованный текст(.encrypt)"; cin >> crypt_text; cout << endl;
				cout << "Укажите файл с ключом:(.key) :"; cin >> key; cout << endl;
				CryptChange* crypt_ch = new CryptChange;
				Encryption = crypt_ch;
				if (!Encryption->GetText(text)) return;
				if (!Encryption->GetKey(key)) return;
				Encryption->Crypt();
				Encryption->WriteEncrypt(crypt_text);
				delete Encryption;
				cout << "Текст зашифрован" << endl;
			}
			else if (com == 2) {

				cout << "Укажите файл с текстом:(.txt) :"; cin >> text; cout << endl;
				cout << "Укажите файл куда запишиться зашифованный текст(.encrypt)"; cin >> crypt_text; cout << endl;
				cout << "Укажите файл с ключом:(.key) :"; cin >> key; cout << endl;
				CryptShift* crypt_ch = new CryptShift;
				Encryption = crypt_ch;
				if (!Encryption->GetText(text)) return;
				if (!Encryption->GetKey(key)) return;
				Encryption->Crypt();
				Encryption->WriteEncrypt(crypt_text);
				delete Encryption;
				cout << "Текст зашифрован" << endl;
			}
			else if (com == 3) {
				cout << "Укажите файл с алфавитом:(.alph)  "; cin >> alphabet; cout << endl;
				cout << "Укажите файл с текстом:(.txt) :"; cin >> text; cout << endl;
				cout << "Укажите файл куда запишиться зашифованный текст(.encrypt)"; cin >> crypt_text; cout << endl;
				cout << "Укажите файл с ключом:(.key) :"; cin >> key; cout << endl;
				CryptGamma* crypt_ch = new CryptGamma;
				Encryption = crypt_ch;
				if (!Encryption->GetAlphabet(alphabet)) return;
				if (!Encryption->GetText(text)) return;
				if (!Encryption->GetKey(key)) return;
				Encryption->Crypt();
				Encryption->WriteEncrypt(crypt_text);
				delete Encryption;
				cout << "Текст зашифрован" << endl;
			}


		}
		else if (com == 2) {

			cout << "Выберите метод расшифровки для:\n" << "1) Шифра заменой\n" << "2)  Шифра перестановкой\n" << "3) Шифра гаммирования \n" << endl;
			com = 0;
			cin >> com; cout << endl;
			if (com == 1) {
				cout << "Укажите файл с зашифрованным текстом:(.encrypt) : "; cin >> crypt_text; cout << endl;
				cout << "Укажите файл куда запишится расшифрванный текст(.txt) : "; cin >> text; cout << endl;
				cout << "Укажите файл с ключом:(.key) : "; cin >> key; cout << endl;
				CryptChange* crypt_ch = new CryptChange;
				Encryption = crypt_ch;
				if (!Encryption->GetEncrypt(crypt_text)) return;
				if (!Encryption->GetKey(key)) return;
				Encryption->DeCrypt();
				Encryption->WriteText(text);
				delete Encryption;
				cout << "Текст расшифрован" << endl;
			}
			else if (com == 2) {
				cout << "Укажите файл с зашифрованным текстом:(.encrypt) : "; cin >> crypt_text; cout << endl;
				cout << "Укажите файл куда запишиться расшифрванный текст(.txt) : "; cin >> text; cout << endl;
				cout << "Укажите файл с ключом:(.key) : "; cin >> key; cout << endl;
				CryptShift* crypt_ch = new CryptShift;
				Encryption = crypt_ch;
				if (!Encryption->GetEncrypt(crypt_text)) return;
				if (!Encryption->GetKey(key)) return;
				Encryption->DeCrypt();
				Encryption->WriteText(text);
				delete Encryption;
				cout << "Текст расшифрован" << endl;
			}

			else if (com == 3) {
				cout << "Укажите файл с алфавитом:(.alph)  "; cin >> alphabet; cout << endl;
				cout << "Укажите файл с зашифрованным текстом:(.encrypt) : "; cin >> crypt_text; cout << endl;
				cout << "Укажите файл куда запишиться расшифрванный текст(.txt) : "; cin >> text; cout << endl;
				cout << "Укажите файл с ключом:(.key) : "; cin >> key; cout << endl;
				CryptGamma* crypt_ch = new CryptGamma;
				Encryption = crypt_ch;
				if (!Encryption->GetAlphabet(alphabet)) return;
				if (!Encryption->GetEncrypt(crypt_text)) return;
				if (!Encryption->GetKey(key)) return;
				Encryption->DeCrypt();
				Encryption->WriteText(text);
				delete Encryption;
				cout << "Текст расшифрован" << endl;
			}

		}
	}
	else if (com == 2) {

			com = 0;
			cout << "Генерация ключа:\n" << "1) Шифр заменой\n" << "2) Шифр перестановкой\n" << "3) Шифр гаммирования \n" << endl;
			cin >> com; cout << endl;

			if (com == 1) {


				cout << "Укажите имя файла для сохранения ключа:(.key)  "; cin >> key; cout << endl;
				cout << "Укажите файл с алфавитом:(.alph)  "; cin >> alphabet; cout << endl;
				CryptChange* crypt_ch = new CryptChange;
				Encryption = crypt_ch;
				if (!Encryption->GetAlphabet(alphabet)) return;
				Encryption->KeyGeneration();
				Encryption->WriteKey(key);
				delete Encryption;
				cout << "Ключ сгенерирован" << endl;
			}
			else if (com == 2) {

				cout << "Укажите имя файла для сохранения ключа:(.key)  "; cin >> key; cout << endl;
				cout << "Укажите размер ключа"; cin >> s_key;
				CryptShift* crypt_ch = new CryptShift(s_key);
				ACrypt* Encryption = crypt_ch;
				Encryption->KeyGeneration();
				Encryption->WriteKey(key);
				delete Encryption;
				cout << "Ключ сгенерирован" << endl;
			}
			else if (com == 3) {
				cout << "Укажите файл с алфавитом:(.alph)  "; cin >> alphabet; cout << endl;
				cout << "Укажите имя файла для сохранения ключа:(.key)  "; cin >> key; cout << endl;
				cout << "Укажите размер ключа "; cin >> s_key;
				CryptGamma* crypt_ch = new CryptGamma(s_key);
				ACrypt* Encryption = crypt_ch;
				if (!Encryption->GetAlphabet(alphabet)) return;
				Encryption->KeyGeneration();
				Encryption->WriteKey(key);
				delete Encryption;
				cout << "Ключ сгенерирован" << endl;
			}
		}

	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	setlocale(LC_ALL, "ru");
	menu();
	return 0;
}


