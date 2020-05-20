#include "CryptChange.h"
#include "ctime"

using namespace std;
using json = nlohmann::json;

CryptChange::CryptChange()
{
	this->algot = "шифр замены";
	this->encrypt["alg_type"] = this->algot;
	this->encrypt["text"] = "";
	this->key["alg_type"] = this->algot;
	this->key["key"] = "";
	this->key_size = 10;
}
/////////////////////////////////////////////////////////////////////////////////////////
void CryptChange::Crypt() {
	
	json tmp = this->key["key"];
	json dkey;
	for (auto i = 0; i < static_cast<int>(tmp.size()); i++) dkey[string(tmp[i][0])] = tmp[i][1];

	string ctext;
	for (auto i = 0; i < static_cast<int>(this->text.get_size()); i++){
        string ssym = this->text[i];
		if (dkey.find(ssym) != dkey.end()) {
			auto ssymbol = dkey[ssym].get<string>();
			ctext.append(ssymbol);
		}
		else ctext.append(ssym);
	}
	
	this->encrypt["text"] = ctext;
	
}
/////////////////////////////////////////////////////////////////////////////////////////
void CryptChange::DeCrypt() {
	json tmp = key["key"];
	json dkey; //Dictionary Key
	for (auto i = 0; i < static_cast<int>(tmp.size()); i++) dkey[string(tmp[i][1])] = tmp[i][0];

	ustring ctext = this->encrypt["text"].get<string>();
	string detext;

	for (auto i = 0; i < static_cast<int>(ctext.get_size()); i++){
        string ssym = ctext[i];
        if (dkey.find(ssym) != dkey.end()) {
            auto symbol = dkey[ssym].get<string>();
            detext.append(symbol);
        }
        else detext.append(ssym);
	}
	this->text = detext;
}
/////////////////////////////////////////////////////////////////////////////////////////
void CryptChange::KeyGeneration() {
	json result;
	auto alp = this->alphabet["alp"];
	auto n = alp.size();
	auto alp2 = alp;
    srand ( time(NULL) );

	for (auto it = alp.begin(); it != alp.end(); ++it) {
		int rval = int((rand() % n));
		json tmp = { *it, alp2[rval] };
		alp2.erase(rval);
		result.push_back(tmp);
		n--;
	}
	this->key["key"] = result;
}
