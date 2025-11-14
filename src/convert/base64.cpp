namespace CONVERT {
  const std::string base64_chars ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  //encoding function
  std::string base64_encode(const std::string& input){
  std::string encoded;
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
  std::string base64_decode(const std::string& encoded) {
  std::string decoded;
    int val = 0;
    int valb = -8;

    for (unsigned char c : encoded) {
        if (c == '=') break;

        size_t index = base64_chars.find(c);
        if (index == std::string::npos) {
            using namespace termcolor;
            std::cout << red << "Invalid Base64 Input: " << reset << underline << yellow << encoded << reset << " at " << magenta << "(" << c << ")?" << reset << std::endl; 
            return "----------\n";
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
}
