#pragma once
#include "ACrypt.h"
#include "json.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include "ustring.h"
#include <ctime>

class CryptChange : public ACrypt
{
private:
	int key_size;
public:
	CryptChange();

	void KeyGeneration() override;
	void Crypt() override;
	void DeCrypt() override;
};


