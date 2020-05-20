#include "CryptGamma.h"
#include <time.h>
using namespace std;
using json = nlohmann::json;

CryptGamma::CryptGamma()
{
	this->algot = "шифр гаммирования";
	this->encrypt["alg_type"] = this->algot;
	this->encrypt["text"] = "";
	this->key["alg_type"] = this->algot;
	this->key["key"] = "";
	this->key_size = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////
CryptGamma::CryptGamma(int s_key)
{
	this->algot = "шифр гаммирования";
	this->encrypt["alg_type"] = this->algot;
	this->encrypt["text"] = "";
	this->key["alg_type"] = this->algot;
	this->key["key"] = "";
	this->key_size = s_key;
}
/////////////////////////////////////////////////////////////////////////////////////////
void CryptGamma::Crypt() {
    auto alp = this->alphabet["alp"];
	auto key = this->key["key"];
    this->key_size = key.size();

    json num_alp;
    json anti_num_alp;
    for (auto i = 0; i < static_cast<int>(alp.size()); i++) {
        num_alp[alp[i].get<string>()] = i + 1;
        anti_num_alp[i + 1] = alp[i];
    }

    json offset;
    for (auto i = 0; i < static_cast<int>(key.size()); i++) offset.push_back(num_alp[key[i].get<string>()]);


    string ctext;
    for (auto i = 0; i < static_cast<int>(this->text.get_size()); i++) {
        if (num_alp.find(this->text[i]) != num_alp.end()) {
            int num = i % this->key_size;
            int new_sym_pos = (num_alp[this->text[i]].get<int>() + offset[num].get<int>()) % alp.size();
            if (new_sym_pos == 0) new_sym_pos = alp.size();
            ctext += anti_num_alp[new_sym_pos];
        }
        else ctext += this->text[i];
    }

	this->encrypt["text"] = ctext;
}
/////////////////////////////////////////////////////////////////////////////////////////
void CryptGamma::DeCrypt() {
    auto alp = this->alphabet["alp"];
	auto key = this->key["key"];
    this->key_size = key.size();

    ustring ctext = this->encrypt["text"].get<string>();

    json num_alp;
    json anti_num_alp;
    for (auto i = 0; i < static_cast<int>(alp.size()); i++) {
        num_alp[alp[i].get<string>()] = i + 1;
        anti_num_alp[i + 1] = alp[i];
    }

    json offset;
    for (auto i = 0; i < static_cast<int>(key.size()); i++) offset.push_back(num_alp[key[i].get<string>()]);


    string detext;
    for (auto i = 0; i < static_cast<int>(ctext.get_size()); i++) {
        if (num_alp.find(ctext[i]) != num_alp.end()) {
            int num = i % this->key_size;
            int new_sym_pos = (num_alp[string(ctext[i])].get<int>() - offset[num].get<int>());
            if (new_sym_pos < 0) new_sym_pos = alp.size() + new_sym_pos;
            if (new_sym_pos == 0) new_sym_pos = alp.size();
            detext += anti_num_alp[new_sym_pos];
        }
        else detext += ctext[i];
    }

	this->text = detext;
}
/////////////////////////////////////////////////////////////////////////////////////////
void CryptGamma::KeyGeneration() {
    json result;
	auto alp = this->alphabet["alp"];
    srand ( time(NULL) );

	for (auto i = 0; i < this->key_size; i++){
		int rval = int((rand() % static_cast<int>(alp.size())));
		result.push_back(alp[rval]);
	}
	this->key["key"] = result;
}
