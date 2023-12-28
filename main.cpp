#include  "modAlphaCipher.h"
using namespace std;
std::wstring toValid(std::wstring& s)
{
    //setup converter
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;

    if (s.empty())
        throw cipher_error("Empty text");

    //use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
    std::wstring tmp(s);
    std::string st = converter.to_bytes(s);
    for (auto & c:tmp) {
        if (!iswalpha(c))
            throw cipher_error(("Text has invalid symbols: ") +st);
        if (iswlower(c))
            c = towupper(c);
    }
    return tmp;
}
int main(int argc, char **argv)
{
    try {
        locale loc("ru_RU.UTF-8");
        locale::global(loc);
        int key;
        wstring text;
        int op;
        wcout<<L"Cipher ready. Input key: ";
        wcin>>key;
        if (!wcin.good()) {
            throw cipher_error("key not valid\n");
        }

        tableCipher cipher(key);
        do {
            wcout<<L"Cipher ready. Input operation (0-exit, 1-encrypt, 2-decrypt): ";
            wcin>>op;
            if (op > 2) {
                throw cipher_error("Illegal operation\n");
            } else if (op >0) {
                wcout<<L"Cipher ready. Input text: ";
                wcin>>text;
                std::wstring vtext=toValid(text);
                if (op==1) {
                    wcout<<L"Encrypted text: "<<cipher.encrypt(vtext)<<endl;
                } else {
                    wcout<<L"Decrypted text: "<<cipher.decrypt(vtext)<<endl;
                }
            }
        } while (op!=0);
    } catch (const cipher_error& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
        return 1;

    }
}
