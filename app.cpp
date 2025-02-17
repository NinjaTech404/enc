#include <iostream>
#include <vector>
#include "enc.h"
using namespace std;
//array that holds all availble encryption
vector<string> encType = {"base64", "base32", "hex", "caesar", "binary"};
int main(int argl, char** args){
    /*START*/

    //first input filter
    if(!args[1])
    { cerr << "\e[1;101mERROR:\e[0;1;31m Choose Encryption\e[1;35m (base64/base32/hex/caesar/binary).\e[0m" << endl; return -1; }

    string type = args[1];  
    bool typeValid = false;
    for(const string& enc : encType) { if(enc == type) typeValid = true; }

    if(!typeValid) 
    { cerr << "\e[1;101mERROR:\e[0;1;31m Invalid Encryption => \e[1;33m(" << type << "),\e[0;1;31m Choose Encryption\e[1;35m (base64/base32/hex/caesar/binary).\e[0m" << endl; return -1; }
    
    //second input filter
    if(!args[2])
    { cerr << "\e[1;101mERROR:\e[0;1;31m Choose \e[1;35m(Encode/Decode).\e[0m" << endl; return -1; }
    string into = args[2];
    if(!(into == "encode" || into == "decode"))
    { cerr << "\e[1;101mERROR:\e[0;1;31m Invalid Operation => \e[1;33m("  << into << "),\e[0;1;31m Choose \e[1;35m(Encode/Decode).\e[0m" << endl; return -1; }

    //third input filter
    if(!args[3]) { cerr << "\e[1;101mERROR:\e[0;1;31m Please Enter The Desired Value.\e[0m" << endl; return -1; }
    string value = args[3];
 
    //input processing adn validation
    if(type == "base64"){
        if(into == "encode"      && base64_encode(value) != "" ) { cout << "\e[1;44mENCODED:\e[0;1;32m "  << base64_encode(value) << "\e[0m" << endl; }
	else if(into == "decode" && base64_decode(value) != "" ) { cout << "\e[1;105mDECODED:\e[0;1;32m " << base64_decode(value) << "\e[0m" << endl; }
    }
    else if(type == "base32"){
        if(into == "encode"      && base32_encode(value) != "" ) { cout << "\e[1;44mENCODED:\e[0;1;32m "  << base32_encode(value) << "\e[0m" << endl; }
	else if(into == "decode" && base32_decode(value) != "" ) { cout << "\e[1;105mDECODED:\e[0;1;32m " << base32_decode(value) << "\e[0m" << endl; }
    }
    else if(type == "hex"){
        if(into == "encode"      && hex_encode(value) != "" ) { cout << "\e[1;44mENCODED:\e[0;1;32m "  << hex_encode(value) << "\e[0m" << endl; }
	else if(into == "decode" && hex_decode(value) != "" ) { cout << "\e[1;105mDECODED:\e[0;1;32m " << hex_decode(value) << "\e[0m" << endl; }
    }
    else if(type == "caesar"){
	if(args[4]){
	    int shift = stoi(args[4]);
            if(into == "encode")      { cout << "\e[1;44mENCODED:\e[0;1;32m "  << caesar(value, shift)  << "\e[0m" << endl; }
            else if(into == "decode") { cout << "\e[1;105mDECODED:\e[0;1;32m " << caesar(value, -shift) << "\e[0m" << endl; }
	}
	else { cerr << "\e[1;101mERROR:\e[0;1;31m Caesar Shift is required, \e[1;35m(INTEGER).\e[0m" << endl; return -1; }
    }
    else if(type == "binary"){
        if(into == "encode"      && binaryEncode(value) != "" ) { cout << "\e[1;44mENCODED:\e[0;1;32m "  << binaryEncode(value) << "\e[0m" << endl; }
        else if(into == "decode" && binaryDecode(value) != "" ) { cout << "\e[1;105mDECODED:\e[0;1;32m " << binaryDecode(value) << "\e[0m" << endl; }
    }

    /*END*/
    return 0;
}
