namespace CONVERT{
  std::string hex_chars = "0123456789ABCDEF"; 
  //encoding function
  std::string hex_encode(const std::string& input){
  std::string encoded;
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
  std::string hex_decode(const std::string& encoded) {
    std::string decoded;
    int val = 0;
    int valb = -8;

    for (const char& c : encoded) {

        size_t index = hex_chars.find(toupper(c));
        if (index == std::string::npos) {
            using namespace termcolor;
            std::cout << red << "Invalid Hex Input: " << reset << underline << yellow << encoded << reset << " at " << magenta << "(" << c << ")?" << reset << std::endl; 
            return "----------\n"; 
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
}
