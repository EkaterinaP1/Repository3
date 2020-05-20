#pragma once
#include <string>
#include <bitset>
#include <stdexcept>
#include <iostream>
using namespace std;
class ustring
{
    public:
    string text;
    public:
        ustring();
        ustring(string text);
        string dump();
        int get_size();
        string operator[] (const int index);
        
    protected:

    private:
};
