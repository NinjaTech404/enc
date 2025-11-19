// Define flag function behavors
auto version_callback = [](int count){ 
    fmt::print("Version 1.5.0\n");
};
auto list_callback = [](int count) {
    std::vector<std::pair<std::string, std::string>> convert = {
        {"--binary", "Convert to binary format"},
        {"--hex", "Convert to hexadecimal format"},
        {"--base32", "Convert to Base32 format"},
        {"--base64", "Convert to Base64 format"},
        {"--caesar", "Apply Caesar cipher encryption"}
    };

    // Header
    fmt::print("\n");
    fmt::print("FORMAT CONVERSION SCHEMES\n");
    fmt::print("{:=<41}\n", "");
    fmt::print("{:<10} {:<10}\n", "FLAG", "DESCRIPTION");
    fmt::print("{:-<41}\n", "");

    // Content
    for (const auto& [flag, description] : convert) {
        fmt::print("{:<10} {:<10}\n", flag, description);
    }
    fmt::print("{:-<41}\n", "");
    fmt::print("\n");

    std::vector<std::pair<std::string, std::string>> dgst = {
      {"--md5", "Generate MD5 hash"},
      {"--sha1", "Generate SHA-1 hash"},
      { "--sha3", "Generate SHA-3 hash"},
      {"--sha256", "Generate SHA-256 hash"},
      {"--crc32", "Generate CRC-32 hash"},
      {"--keccak", "Generate Keccak hash"}
    };

  // Header
  fmt::print("\n");
  fmt::print("HASHING ALGORITHMS SCHEMES\n");
  fmt::print("{:=<41}\n", "");
  fmt::print("{:<10} {:<10}\n", "FLAG", "DESCRIPTION");
  fmt::print("{:-<41}\n", "");

  // Content
  for (const auto& [flag, description] : dgst) {
    fmt::print("{:<10} {:<10}\n", flag, description);
  }
  fmt::print("{:-<41}\n", "");
  fmt::print("\n");
};

void format_not_specified (void){
  std::vector<std::pair<std::string, std::string>> convert = {
        {"--binary", "Convert to binary format"},
        {"--hex", "Convert to hexadecimal format"},
        {"--base32", "Convert to Base32 format"},
        {"--base64", "Convert to Base64 format"},
        {"--caesar", "Apply Caesar cipher encryption"}
    };

    // Header
    fmt::print("\n");
    fmt::print("FORMAT CONVERSION SCHEMES\n");
    fmt::print("{:=<41}\n", "");
    fmt::print("{:<10} {:<10}\n", "FLAG", "DESCRIPTION");
    fmt::print("{:-<41}\n", "");

    // Content
    for (const auto& [flag, description] : convert) {
        fmt::print("{:<10} {:<10}\n", flag, description);
    }
    fmt::print("{:-<41}\n", "");
    fmt::print("\n");

}

void hash_not_specified(void){
    std::vector<std::pair<std::string, std::string>> dgst = {
      {"--md5", "Generate MD5 hash"},
      {"--sha1", "Generate SHA-1 hash"},
      { "--sha3", "Generate SHA-3 hash"},
      {"--sha256", "Generate SHA-256 hash"},
      {"--crc32", "Generate CRC-32 hash"},
      {"--keccak", "Generate Keccak hash"}
    };

  // Header
  fmt::print("\n");
  fmt::print("HASHING ALGORITHMS SCHEMES\n");
  fmt::print("{:=<41}\n", "");
  fmt::print("{:<10} {:<10}\n", "FLAG", "DESCRIPTION");
  fmt::print("{:-<41}\n", "");

  // Content
  for (const auto& [flag, description] : dgst) {
    fmt::print("{:<10} {:<10}\n", flag, description);
  }
  fmt::print("{:-<41}\n", "");
  fmt::print("\n");
}
