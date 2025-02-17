#include <string>
std::string caesar(std::string text, int shift) {
  std::string result = "";
  for (char& c : text) {
    if (isalpha(c)) {
      char start = isupper(c) ? 'A' : 'a';
      c = start + (c - start + shift) % 26;
      if (c < start) c += 26;
    }
  }
  return text;
}
