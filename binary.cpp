#include <string>
#include <bitset>
#include <algorithm>

std::string binaryEncode(const std::string& text) {
  std::string binaryString;
  for (char c : text) {
    std::bitset<8> bits(c);
    binaryString += bits.to_string();
  }
  return binaryString;
}

std::string binaryDecode(const std::string& binaryString) {
  std::string text;
  if (binaryString.length() % 8 != 0) { cerr << "\e[1;101mERROR:\e[0;1;31m Invalid Binary Input: \e[1;33m(" << binaryString << ").\e[0m" << endl; return ""; }
  for (size_t i = 0; i < binaryString.length(); i += 8) {
    std::string byte = binaryString.substr(i, 8);
    char c = static_cast<char>(std::bitset<8>(byte).to_ulong());
    text += c;
  }
  return text;
}
