#pragma once
#include "ACrypt.h"
#include "json.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include "ustring.h"

using namespace std;
using json = nlohmann::json;

class CryptShift : public ACrypt
{
private:
	int key_size;
public:
    CryptShift();
	CryptShift(int s_key);

	void KeyGeneration() override;
	void Crypt() override;
	void DeCrypt() override;
};


