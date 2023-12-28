#include  "tableCipher.h"
#include <string>

using namespace std;

std::wstring tableCipher::encrypt(std::wstring& open_text)
{
    wstring tabl = open_text;
    int dl, nstrok, index, x;
    while (tabl.size() % key1 != 0) {
        tabl+=L"_";
    }
    open_text = tabl;
    dl = tabl.size();
    nstrok = (dl - 1) / key1 + 1;
    x = 0;
    wstring encrypted;
    for (int i = key1; i > 0; i--) {
        for (int j = 0; j < nstrok; j++) {
            index = i+key1*j;
            //wcout<<index<<endl;
            if (index-1 < dl) {
                tabl[x] = open_text[index-1];
                x++;
            }
        }
    }
    return tabl;
}

std::wstring tableCipher::decrypt(std::wstring& cipher_text)
{
    wstring tabl = cipher_text;
    int dl, nstrok, index, x;
    dl = cipher_text.length();
    nstrok = (dl - 1) / key1 + 1;
    x = 0;
    for (int i = key1; i > 0; i--) {
        for (int j = 0; j < nstrok; j++) {
            index = i+key1*j;
            if (index-1 < dl) {
                tabl[index-1] = cipher_text[x];
                x++;
            }
        }
    }
    return tabl;
}
