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

// >======> Reading From File <======<
std::pair<std::string, bool> read_file (std::string file_name){
  std::ifstream file(file_name.c_str()); // initilizing the input file dstream object
  if (!file.is_open()){
    return std::pair<std::string, bool>(fmt::format("The path ({}) to the file is not found or doesn't exist!", file_name), false);
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  file.close();
  return std::pair<std::string, bool>(std::string(buffer.str()), true);

}


// >======> Reading From File <======<
std::pair<std::string, bool> write_file (std::string file_name, std::string content, std::pair<std::string, std::string> labels){
  std::ofstream file;
  file.open(file_name.c_str());
  if(!file.is_open()){
    return std::pair<std::string, bool>(fmt::format("Faild to create the file ({})!", file_name), false);
  }
  file << BorderFormatter::format(content, 50, '=', labels.first, labels.second);
  file.close();
  return std::pair<std::string, bool>(fmt::format("Result has been stored in ({})!", file_name), true);
}
