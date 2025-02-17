#include <string>
using namespace std;
const string base64_chars ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
//encoding function
string base64_encode(const string& input){
   string encoded;
   int val = 0;
   int valb = -6;
   for (unsigned char c : input){
       val = (val << 8) + c;
       valb += 8;
       while(valb >= 0){
           encoded.push_back(base64_chars[(val >> valb) & 0x3F]);
           valb -= 6;
       }
   }
   if(valb > -6){
       encoded.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
   }
   while(encoded.size() % 4){
       encoded.push_back('=');
   }
   return encoded;
}
//decoding finction
string base64_decode(const string& encoded) {
    string decoded;
    int val = 0;
    int valb = -8;

    for (unsigned char c : encoded) {
        if (c == '=') break;

        size_t index = base64_chars.find(c);
        if (index == string::npos) {
            cerr << "\e[1;101mERROR:\e[0;1;31m Invalid Base64 character: \e[1;33m(" << c << ")\e[0m" << endl;
            return "";
        }

        val = (val << 6) | index;
        valb += 6;

        if (valb >= 0) {
            decoded.push_back((val >> valb) & 0xFF);
            valb -= 8;
        }
    }

    return decoded;
}
