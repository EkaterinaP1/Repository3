#include "CryptShift.h"
#include <time.h>

using namespace std;
using json = nlohmann::json;

CryptShift::CryptShift(int s_key)
{
	this->algot = "шифр перестановки";
	this->encrypt["alg_type"] = this->algot;
	this->encrypt["text"] = "";
	this->key["alg_type"] = this->algot;
	this->key["key"] = "";
	this->key_size = s_key;
}
/////////////////////////////////////////////////////////////////////////////////////////
CryptShift::CryptShift()
{
	this->algot = "шифр перестановки";
	this->encrypt["alg_type"] = this->algot;
	this->encrypt["text"] = "";
	this->key["alg_type"] = this->algot;
	this->key["key"] = "";
	this->key_size = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////
void CryptShift::Crypt() {
	json tmp = this->key["key"];
	this->key_size = tmp.size();
	json dkey;

	for (auto i = 0; i < static_cast<int>(tmp.size()); i++) dkey[to_string(tmp[i][1])] = tmp[i][0];

	string ctext = "";

	auto tsize = this->text.get_size();
	int hsize = tsize / this->key_size + ((tsize % dkey.size() != 0)? 1: 0);


    string** Arr = new string* [dkey.size()];
	for (int i = 0; i < static_cast<int>(dkey.size()); i++)
		Arr[i] = new string[hsize];

	auto it = 0;
	for (int i = 0; i < hsize; i++)
	{
		for (int j = 0; j < static_cast<int>(dkey.size()); j++)
		{
			if (it < static_cast<int>(this->text.get_size())) {
				Arr[j][i] = this->text[it];
				it++;
			} else Arr[j][i] = "-";
		}
	}

	for (int i = 0; i < static_cast<int>(dkey.size()); i++)
	{
		for (int j = 0; j < hsize; j++)
		{
		    auto tt = dkey[to_string(i)].get<int>();
			ctext += Arr[tt][j];
		}
	}
	this->encrypt["text"] = ctext;
}
/////////////////////////////////////////////////////////////////////////////////////////
void CryptShift::DeCrypt() {
	json tmp = this->key["key"];
	this->key_size = tmp.size();
	json dkey;

	for (auto i = 0; i < static_cast<int>(tmp.size()); i++) dkey[to_string(tmp[i][0])] = tmp[i][1];//


	string detext = "";
	ustring ctext = this->encrypt["text"].get<string>();

	auto tsize = ctext.get_size();
	int hsize = tsize / dkey.size() + ((tsize % dkey.size() != 0) ? 1 : 0);

	string** Arr = new string* [dkey.size()];
	for (int i = 0; i < static_cast<int>(dkey.size()); i++)
		Arr[i] = new string[hsize];

	auto it = 0;
    for (auto i = 0; i < static_cast<int>(dkey.size()); i++)
	{
		for (auto j = 0; j < hsize; j++)
		{
			if (it < static_cast<int>(ctext.get_size())) {
				Arr[i][j] = ctext[it];
				it++;
			} else Arr[i][j] = "-";
		}
	}

	for (auto i = 0; i < hsize; i++)
	{
		for (auto j = 0; j < static_cast<int>(dkey.size()); j++)
		{
			auto tt = dkey[to_string(j)].get<int>();
			detext += Arr[tt][i];
		}
	}

	int countd = 0;
	for (auto rit = detext.crbegin(); rit != detext.crbegin() + static_cast<int>(dkey.size()); ++rit){
		if (*rit == '-') countd++;
		else break;
	}
	detext.erase(detext.size() - countd);

	this->text = detext;
}
/////////////////////////////////////////////////////////////////////////////////////////
void CryptShift::KeyGeneration() {
	json result;
	json tkey;

	for (auto i = 0; i < this->key_size; i++) {
		tkey.push_back(i);
	}
	srand ( time(NULL) );

	for (auto i = 0; i < this->key_size; i++) {
		int rval = int((rand() % (this->key_size - i)));
		json tmp = { i, tkey[rval] };
		tkey.erase(rval);
		result.push_back(tmp);
	}
	this->key["key"] = result;
}
