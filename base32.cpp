#include <string>
using namespace std;
//encoding function
string base32_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
string base32_encode(const string& input) {
    string encoded;
    int val = 0;
    int valb = -5;
    for (const char& c : input) {
        val = (val << 8) | c;
        valb += 8;
        while (valb >= 0) {
            encoded.push_back(base32_chars[(val >> valb) & 0x1F]);
            valb -= 5;
        }
    }
    if (valb > -5) {
        encoded.push_back(base32_chars[(val << 8) >> (valb + 8) & 0x1F]);
    }
    while (encoded.size() % 8) {
        encoded.push_back('=');
    }
    return encoded;
}
//decoding function
string base32_decode(const string& encoded) {
    string decoded;
    int val = 0;
    int valb = -8;

    for (const char& c : encoded) {
        if (c == '=') break;

        size_t index = base32_chars.find(c);
        if (index == string::npos) {

            cerr << "\e[1;101mERROR:\e[0;1;31m Invalid Base32 character: \e[1;33m(" << c << ").\e[0m" << endl;
            return "";
        }

        val = (val << 5) | index;
        valb += 5;

        if (valb >= 0) {
            decoded.push_back((val >> valb) & 0xFF);
            valb -= 8;
        }
    }

    return decoded;
}
