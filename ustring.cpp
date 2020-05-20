#include "ustring.h"

ustring::ustring()
{
    this->text = "";
}
/////////////////////////////////////////////////////////////////////////////////////////
ustring::ustring(string text)
{
    this->text = text;
}
/////////////////////////////////////////////////////////////////////////////////////////
int ustring::get_size(){
    auto i = 0;
	int ussize = 0;     
	while (i < static_cast<int>(this->text.size())){ 
        bitset<8> b(this->text[i]);
        if (b[7] == 0) {
            i++;
            ussize++;
        } else {
            int j = 0;
            while (b[7-j] == 1) j++;
            i = i + j;
            ussize++;
        }
	}
	return ussize;
}
/////////////////////////////////////////////////////////////////////////////////////////
string ustring::operator[] (const int index)
{
    if (index < 0 or this->get_size() <= index)
        throw out_of_range{"ustring::operator[]"};
    int ui = 0;
    int i = 0;
    int j = 0;        
    do {
        i += j;
        j = 0;
        bitset<8> b(this->text[i]);
        if (b[7] == 0) {
            j = 1;
        } else {
            while (b[7-j] == 1) j++;
        }
        ui++;
    } while(ui <= index);
    string ssym = this->text.substr(i,j);

    return ssym;
}
/////////////////////////////////////////////////////////////////////////////////////////
string ustring::dump(){
    return this->text;
}
