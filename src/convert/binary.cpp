#include <bitset>
#include <algorithm>
namespace CONVERT{
  std::string binary_encode(const std::string& text) {
    std::string binaryString;
    for (char c : text) {
      std::bitset<8> bits(c);
      binaryString += bits.to_string();
    }
    return binaryString;
  }

  std::string binary_decode(const std::string& binaryString) {
    std::string text;
    if (binaryString.length() % 8 != 0) {
      using namespace termcolor;
      std::cout << bright_red << "Invalid Binary Input: " << reset << yellow << underline << binaryString << reset << std::endl;
      return "----------\n"; 
    }
    for (size_t i = 0; i < binaryString.length(); i += 8) {
      std::string byte = binaryString.substr(i, 8);
      char c;
      try {
        c = static_cast<char>(std::bitset<8>(byte).to_ulong()); 
      }
      catch (const std::invalid_argument& error){
      using namespace termcolor;
        std::cout << bright_red << "Invalid Binary Input: " << reset << yellow << underline << byte << reset << std::endl;
        return "----------\n"; 
      }
      text += c;
    }
    return text;
  }
}
