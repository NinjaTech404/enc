#include <iostream>
#include <string>
using namespace std;
string hex_chars = "0123456789ABCDEF"; 
//encoding function
string hex_encode(const string& input){
    string encoded;
    int val = 0;
    int valb = -4;
    for(const char c : input){
	val = (val << 8) | c;
	valb += 8;
	while(valb >= 0){
            encoded.push_back(hex_chars[(val >> valb) & 0x0F]);
	    valb -= 4;
	}
    }
    if(valb > -4){
        encoded.push_back(hex_chars[((val << 8) >> (valb + 8)) & 0x0F]);
    }
    return encoded;
}
//decoding function
string hex_decode(const string& encoded) {
    string decoded;
    int val = 0;
    int valb = -8;

    for (const char& c : encoded) {

        size_t index = hex_chars.find(toupper(c));
        if (index == string::npos) {
            cerr << "\e[1;101mERROR:\e[0;1;31m Invalid hexadecimal character: \e[1;33m(" << c << ").\e[0m" << endl;
            return "";
        }

        val = (val << 4) | index;
        valb += 4;

        if (valb >= 0) {
            decoded.push_back((val >> valb) & 0xFF);
            valb -= 8;
        }
    }

    return decoded;
}
