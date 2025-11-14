namespace CONVERT{
  //encoding function
  std::string base32_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
  std::string base32_encode(const std::string& input) {
    std::string encoded;
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
  std::string base32_decode(const std::string& encoded) {
    std::string decoded;
    int val = 0;
    int valb = -8;

    for (const char& c : encoded) {
        if (c == '=') break;

        size_t index = base32_chars.find(c);
        if (index == std::string::npos) {
            using namespace termcolor;
            std::cout << red << "Invalid Base32 Input: " << reset << underline << yellow << encoded << reset << " at " << magenta << "(" << c << ")?" << reset << std::endl; 
            return "----------\n"; 
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
}
