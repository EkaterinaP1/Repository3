#pragma once
#include <string>
#include "json.hpp"
#include <fstream>
#include <iostream>

#include "ustring.h"

using namespace std;
using json = nlohmann::json;

//Abstract Crypt Class
class ACrypt
{
protected:
	string algot;
	json key;
	json alphabet;
	ustring text;
	json encrypt;
public:
    //ACrypt();
 

	virtual void KeyGeneration() = 0;
	virtual void Crypt() = 0;
	virtual void DeCrypt() = 0;
public:
	bool GetAlphabet(string name);
	bool GetKey(string name);
	bool GetText(string name);
	bool GetEncrypt(string name);

	void WriteKey(string name);
	void WriteText(string name);
	void WriteEncrypt(string name);


};
