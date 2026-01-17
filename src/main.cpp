#include<main.hpp>
int main (int argc, char ** argv){
  CLI::App app("A C++ CLI toolkit for Encoding/Decoding Data\nAlso vist \e[36mhttps://github.com/NinjaTech404/enc\e[0m"); // initializing the CLI App Flags/Options
  app.get_formatter()->right_column_width(80); // -> adjusting the help output layout
  /* >=========> Add new options/flags here <=========< */
  app.add_flag_function("--version, -v", version_callback, "Print the app version");
  app.add_flag_function("--list, -l", list_callback, "to list all available conversion formats and hasing algorithms");


  /* >=========> subcommands <=========< */ 
  app.require_subcommand(0, 1);

  /* >---------> dgst command <---------< */
  auto dgst_command = app.add_subcommand("dgst", "To use hashing algorithms (Default md5 in hex)");

  /* >---------> convert command <---------< */
  auto convert_command = app.add_subcommand("convert", "To use converting schemes (Default hex)");

  // ==> convert options
  std::string input_option, output_option;
  int32_t caesar_shift(0); 
  CLI::Option* convert_input_op = convert_command->add_option("--input,-i", input_option, "Accept a value (-i <value> or --input=<value>)");
  convert_command->add_option("--output,-o", output_option, "Generate the output in a desired file (-o <file> or --output=<file>)")->needs(convert_input_op);
  CLI::Option* caesar_option = convert_command->add_option("--shift,-s", caesar_shift, "Specify the shift number for caesar cipher");

  // ==> convert flags
  bool file_flag(0), binary_flag(0), hex_flag(0), base32_flag(0), base64_flag(0), caesar_flag(0), enc_flag(0), dec_flag;
  CLI::Option* file_f = convert_command->add_flag("--file,-f", file_flag, "Accept the input value as a file name")->needs(convert_input_op);
  CLI::Option* binary_f = convert_command->add_flag("--binary", binary_flag, "Convert into binary")->needs(convert_input_op);
  CLI::Option* hex_f = convert_command->add_flag("--hex", hex_flag, "Convert into hexadecimal")->needs(convert_input_op);
  CLI::Option* base32_f = convert_command->add_flag("--base32", base32_flag, "Convert into base32")->needs(convert_input_op);
  CLI::Option* base64_f = convert_command->add_flag("--base64", base64_flag, "Convert into base64")->needs(convert_input_op);
  CLI::Option* caesar_f = convert_command->add_flag("--caesar", caesar_flag, "Apply caesar cipher")->needs(convert_input_op);
  CLI::Option* enc_f = convert_command->add_flag("--encode, -e", enc_flag, "to encode the value to the specified format")->needs(convert_input_op);
  CLI::Option* dec_f = convert_command->add_flag("--decode, -d", dec_flag, "to decode the value from the specified format")->needs(convert_input_op);

  // ==> convert flag configurations
  binary_f->excludes(hex_f, base32_f, base64_f, caesar_f);
  hex_f->excludes(binary_f, base32_f, base64_f, caesar_f);
  base32_f->excludes(binary_f, hex_f, base64_f, caesar_f);
  base64_f->excludes(binary_f, hex_f, base32_f, caesar_f);
  enc_f->excludes(dec_f);
  dec_f->excludes(enc_f);
  
  // ==> Caesar Cipher flag/option configurations
  caesar_f->excludes(binary_f, hex_f, base32_f, base64_f, enc_f, dec_f);
  caesar_option->excludes(binary_f, hex_f, base32_f, base64_f, enc_f, dec_f);
  caesar_f->needs(caesar_option);
  caesar_option->needs(caesar_f);

  // ==> dgst options
  std::string dgst_input_option, dgst_output_option;
  CLI::Option* dgst_input_op = dgst_command->add_option("--input,-i", dgst_input_option, "Accept a value (-i <value> or --input=<value>)");
  dgst_command->add_option("--output,-o", dgst_output_option, "Generate the output in a desired file (-o <file> or --output=<file>)")->needs(dgst_input_op);

  // ==> dgst flags 
  bool dsgt_file_flag(0), md5_flag(0), sha1_flag(0), sha3_flag(0), sha256_flag(0), crc32_flag(0), keccak_flag(0);
  CLI::Option* dgst_file_f = dgst_command->add_flag("--file,-f", dsgt_file_flag, "Accept the input value as a file name");
  CLI::Option* md5_f = dgst_command->add_flag("--md5", md5_flag, "Generate an MD5 hash of --input value")->needs(dgst_input_op);
  CLI::Option* sha1_f = dgst_command->add_flag("--sha1", sha1_flag, "Generate a SHA-1 hash of --input value")->needs(dgst_input_op);
  CLI::Option* sha3_f = dgst_command->add_flag("--sha3", sha3_flag, "Generate a SHA-3 hash of --input value")->needs(dgst_input_op);
  CLI::Option* sha256_f = dgst_command->add_flag("--sha256", sha256_flag, "Generate a SHA-256 hash of --input value")->needs(dgst_input_op);
  CLI::Option* crc32_f = dgst_command->add_flag("--crc32", crc32_flag, "Generate a CRC-32 hash of --input value")->needs(dgst_input_op);
  CLI::Option* keccak_f = dgst_command->add_flag("--keccak", keccak_flag, "Generate a Keccak hash of --input value")->needs(dgst_input_op);

  // ==> dgst flag configurations
  md5_f->excludes(sha1_f, sha3_f, sha256_f, crc32_f, keccak_f);
  sha1_f->excludes(md5_f, sha3_f, sha256_f, crc32_f, keccak_f);
  sha3_f->excludes(md5_f, sha1_f, sha256_f, crc32_f, keccak_f);
  sha256_f->excludes(md5_f, sha1_f, sha3_f, crc32_f, keccak_f);
  crc32_f->excludes(md5_f, sha1_f, sha3_f, sha256_f, keccak_f);
  keccak_f->excludes(md5_f, sha1_f, sha3_f, sha256_f, crc32_f);

  // ==> CLI App parser
  CLI11_PARSE(app, argc, argv); //Flags/Options Parser
  
  /* >=========> subcommands actions <=========< */ 
  std::string output_value = ""; // => Stores the result

  /* >=========> convert command actions <=========< */
  if(convert_command->parsed()){  
    std::pair<std::string, bool> file_data = read_file(input_option); // => Stores the content of pathed file
    /* >---------> Binary <---------< */
    if(binary_flag){
        /* >---------> Binary Encoding <---------< */
        if(enc_flag) { 
            if(file_flag){
                using namespace termcolor;
                if(!file_data.second){
                    std::cout << red << bold << underline << file_data.first << reset << std::endl; 
                    return -1;
                }
                output_value = CONVERT::binary_encode(file_data.first);
                if (!output_option.empty()){
                  std::pair<std::string, bool> file_status = write_file(output_option, output_value, std::pair<std::string, std::string>("BINARY ENCODED BEGIN","BINARY ENCODED END"));
                  if (!file_status.second){ 
                    std::cout << red << bold << underline << file_status.first << reset << std::endl;
                    fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("BINARY ENCODED BEGIN"), std::string("BINARY ENCODED END")));
                    return -1;
                  }
                  std::cout << green << bold << underline << file_status.first << reset << std::endl;
                  return 0;
                }
                fmt::print("Binary({}): {}\n\n", input_option, fmt::format(fg(fmt::color::light_green), "{}", output_value)); 
                return 0;
            }
            output_value = CONVERT::binary_encode(input_option);
            if (!output_option.empty()){
                using namespace termcolor;
                std::pair<std::string, bool> file_status = write_file(output_option, output_value, std::pair<std::string, std::string>("BINARY ENCODED BEGIN","BINARY ENCODED END"));
                if (!file_status.second){ 
                  std::cout << red << bold << underline << file_status.first << reset << std::endl;
                  fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("BINARY ENCODED BEGIN"), std::string("BINARY ENCODED END")));
                  return -1;
                }
                std::cout << green << bold << underline << file_status.first << reset << std::endl;
                return 0;
            }
            fmt::print("Binary: {}\n\n", fmt::format(fg(fmt::color::light_green), "{}", output_value));
            return 0;
        }
        /* >---------> Binary Decoding <---------< */
        else if(dec_flag) {
            if(file_flag){
                using namespace termcolor;
                if(!file_data.second){
                    std::cout << red << bold << underline << file_data.first << reset << std::endl; 
                    return -1;
                }
                output_value = CONVERT::binary_decode(file_data.first);
                if (!output_option.empty()){
                  std::pair<std::string, bool> file_status = write_file(output_option, output_value, std::pair<std::string, std::string>("BINARY DECODED BEGIN","BINARY DECODED END"));
                  if (!file_status.second){ 
                    std::cout << red << bold << underline << file_status.first << reset << std::endl;
                    fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("BINARY DECODED BEGIN"), std::string("BINARY DECODED END")));
                    return -1;
                  }
                  std::cout << green << bold << underline << file_status.first << reset << std::endl;
                  return 0;
                }
                fmt::print("Binary({}): {}\n", input_option, fmt::format(fg(fmt::color::light_green), "{}", output_value)); 
                return 0;
            }
            output_value = CONVERT::binary_decode(input_option);
            if (!output_option.empty()){
                using namespace termcolor;
                std::pair<std::string, bool> file_status = write_file(output_option, output_value, std::pair<std::string, std::string>("BINARY DECODED BEGIN","BINARY DECODED END"));
                if (!file_status.second){ 
                  std::cout << red << bold << underline << file_status.first << reset << std::endl;
                  fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("BINARY DECODED BEGIN"), std::string("BINARY DECODED END")));
                  return -1;
                }
                std::cout << green << bold << underline << file_status.first << reset << std::endl;
                return 0;
            }
            fmt::print("Binary: {}\n", fmt::format(fg(fmt::color::light_green), "{}", output_value));
            return 0;
        }
        /* >---------> Binary Requirements <---------< */
        else {
            fmt::print("--encode,-e OR --decode,-d flag is required\n");
            return -1;
        }
    }
    
    /* >---------> Hex <---------< */
    else if(hex_flag){
        /* >---------> Hex Encoding <---------< */
        if(enc_flag) { 
            if(file_flag){
                using namespace termcolor;
                if(!file_data.second){
                    std::cout << red << bold << underline << file_data.first << reset << std::endl; 
                    return -1;
                }
                output_value = CONVERT::hex_encode(file_data.first);
                if (!output_option.empty()){
                  std::pair<std::string, bool> file_status = write_file(output_option, output_value, std::pair<std::string, std::string>("HEX ENCODED BEGIN","HEX ENCODED END"));
                  if (!file_status.second){ 
                    std::cout << red << bold << underline << file_status.first << reset << std::endl;
                    fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("HEX ENCODED BEGIN"), std::string("HEX ENCODED END")));
                    return -1;
                  }
                  std::cout << green << bold << underline << file_status.first << reset << std::endl;
                  return 0;
                }
                fmt::print("Hex({}): {}\n\n", input_option, fmt::format(fg(fmt::color::light_green), "{}", output_value)); 
                return 0;
            }
            output_value = CONVERT::hex_encode(input_option);
            if (!output_option.empty()){
                using namespace termcolor;
                std::pair<std::string, bool> file_status = write_file(output_option, output_value, std::pair<std::string, std::string>("HEX ENCODED BEGIN","HEX ENCODED END"));
                if (!file_status.second){ 
                  std::cout << red << bold << underline << file_status.first << reset << std::endl;
                  fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("HEX ENCODED BEGIN"), std::string("HEX ENCODED END")));
                  return -1;
                }
                std::cout << green << bold << underline << file_status.first << reset << std::endl;
                return 0;
            }
            fmt::print("Hex: {}\n\n", fmt::format(fg(fmt::color::light_green), "{}", output_value));
            return 0;
        }
        /* >---------> Hex Decoding <---------< */
        else if(dec_flag) {
            if(file_flag){
                using namespace termcolor;
                if(!file_data.second){
                    std::cout << red << bold << underline << file_data.first << reset << std::endl; 
                    return -1;
                }
                output_value = CONVERT::hex_decode(file_data.first);
                if (!output_option.empty()){
                  std::pair<std::string, bool> file_status = write_file(output_option, output_value, std::pair<std::string, std::string>("HEX DECODED BEGIN","HEX DECODED END"));
                  if (!file_status.second){ 
                    std::cout << red << bold << underline << file_status.first << reset << std::endl;
                    fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("HEX DECODED BEGIN"), std::string("HEX DECODED END")));
                    return -1;
                  }
                  std::cout << green << bold << underline << file_status.first << reset << std::endl;
                  return 0;
                }
                fmt::print("Hex({}): {}\n", input_option, fmt::format(fg(fmt::color::light_green), "{}", output_value)); 
                return 0;
            }
            output_value = CONVERT::hex_decode(input_option);
            if (!output_option.empty()){
                using namespace termcolor;
                std::pair<std::string, bool> file_status = write_file(output_option, output_value, std::pair<std::string, std::string>("HEX DECODED BEGIN","HEX DECODED END"));
                if (!file_status.second){ 
                  std::cout << red << bold << underline << file_status.first << reset << std::endl;
                  fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("HEX DECODED BEGIN"), std::string("HEX DECODED END")));
                  return -1;
                }
                std::cout << green << bold << underline << file_status.first << reset << std::endl;
                return 0;
            }
            fmt::print("Hex: {}\n", fmt::format(fg(fmt::color::light_green), "{}", output_value));
            return 0;
        }
        /* >---------> Hex Requirements <---------< */
        else {
            fmt::print("--encode,-e OR --decode,-d flag is required\n");
            return -1;
        }
    }
    
    /* >---------> Base32 <---------< */
    else if(base32_flag){
        /* >---------> Base32 Encoding <---------< */
        if(enc_flag) { 
            if(file_flag){
                using namespace termcolor;
                if(!file_data.second){
                    std::cout << red << bold << underline << file_data.first << reset << std::endl; 
                    return -1;
                }
                output_value = CONVERT::base32_encode(file_data.first);
                if (!output_option.empty()){
                  std::pair<std::string, bool> file_status = write_file(output_option, output_value, std::pair<std::string, std::string>("BASE32 ENCODED BEGIN","BASE32 ENCODED END"));
                  if (!file_status.second){ 
                    std::cout << red << bold << underline << file_status.first << reset << std::endl;
                    fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("BASE32 ENCODED BEGIN"), std::string("BASE32 ENCODED END")));
                    return -1;
                  }
                  std::cout << green << bold << underline << file_status.first << reset << std::endl;
                  return 0;
                }
                fmt::print("Base32({}): {}\n\n", input_option, fmt::format(fg(fmt::color::light_green), "{}", output_value)); 
                return 0;
            }
            output_value = CONVERT::base32_encode(input_option);
            if (!output_option.empty()){
                using namespace termcolor;
                std::pair<std::string, bool> file_status = write_file(output_option, output_value, std::pair<std::string, std::string>("BASE32 ENCODED BEGIN","BASE32 ENCODED END"));
                if (!file_status.second){ 
                  std::cout << red << bold << underline << file_status.first << reset << std::endl;
                  fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("BASE32 ENCODED BEGIN"), std::string("BASE32 ENCODED END")));
                  return -1;
                }
                std::cout << green << bold << underline << file_status.first << reset << std::endl;
                return 0;
            }
            fmt::print("Base32: {}\n\n", fmt::format(fg(fmt::color::light_green), "{}", output_value));
            return 0;
        }
        /* >---------> Base32 Decoding <---------< */
        else if(dec_flag) {
            if(file_flag){
                using namespace termcolor;
                if(!file_data.second){
                    std::cout << red << bold << underline << file_data.first << reset << std::endl; 
                    return -1;
                }
                output_value = CONVERT::base32_decode(file_data.first);
                if (!output_option.empty()){
                  std::pair<std::string, bool> file_status = write_file(output_option, output_value, std::pair<std::string, std::string>("BASE32 DECODED BEGIN","BASE32 DECODED END"));
                  if (!file_status.second){ 
                    std::cout << red << bold << underline << file_status.first << reset << std::endl;
                    fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("BASE32 DECODED BEGIN"), std::string("BASE32 DECODED END")));
                    return -1;
                  }
                  std::cout << green << bold << underline << file_status.first << reset << std::endl;
                  return 0;
                }
                fmt::print("Base32({}): {}\n", input_option, fmt::format(fg(fmt::color::light_green), "{}", output_value)); 
                return 0;
            }
            output_value = CONVERT::base32_decode(input_option);
            if (!output_option.empty()){
                using namespace termcolor;
                std::pair<std::string, bool> file_status = write_file(output_option, output_value, std::pair<std::string, std::string>("BASE32 DECODED BEGIN","BASE32 DECODED END"));
                if (!file_status.second){ 
                  std::cout << red << bold << underline << file_status.first << reset << std::endl;
                  fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("BASE32 DECODED BEGIN"), std::string("BASE32 DECODED END")));
                  return -1;
                }
                std::cout << green << bold << underline << file_status.first << reset << std::endl;
                return 0;
            }
            fmt::print("Base32: {}\n", fmt::format(fg(fmt::color::light_green), "{}", output_value));
            return 0;
        }
        /* >---------> Base32 Requirements <---------< */
        else {
            fmt::print("--encode,-e OR --decode,-d flag is required\n");
            return -1;
        }
    }
    
    /* >---------> Base64 <---------< */
    else if(base64_flag){
        /* >---------> Base64 Encoding <---------< */
        if(enc_flag) { 
            if(file_flag){
                using namespace termcolor;
                if(!file_data.second){
                    std::cout << red << bold << underline << file_data.first << reset << std::endl; 
                    return -1;
                }
                output_value = CONVERT::base64_encode(file_data.first);
                if (!output_option.empty()){
                  std::pair<std::string, bool> file_status = write_file(output_option, output_value, std::pair<std::string, std::string>("BASE64 ENCODED BEGIN","BASE64 ENCODED END"));
                  if (!file_status.second){ 
                    std::cout << red << bold << underline << file_status.first << reset << std::endl;
                    fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("BASE64 ENCODED BEGIN"), std::string("BASE64 ENCODED END")));
                    return -1;
                  }
                  std::cout << green << bold << underline << file_status.first << reset << std::endl;
                  return 0;
                }
                fmt::print("Base64({}): {}\n\n", input_option, fmt::format(fg(fmt::color::light_green), "{}", output_value)); 
                return 0;
            }
            output_value = CONVERT::base64_encode(input_option);
            if (!output_option.empty()){
                using namespace termcolor;
                std::pair<std::string, bool> file_status = write_file(output_option, output_value, std::pair<std::string, std::string>("BASE64 ENCODED BEGIN","BASE64 ENCODED END"));
                if (!file_status.second){ 
                  std::cout << red << bold << underline << file_status.first << reset << std::endl;
                  fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("BASE64 ENCODED BEGIN"), std::string("BASE64 ENCODED END")));
                  return -1;
                }
                std::cout << green << bold << underline << file_status.first << reset << std::endl;
                return 0;
            }
            fmt::print("Base64: {}\n\n", fmt::format(fg(fmt::color::light_green), "{}", output_value));
            return 0;
        }
        /* >---------> Base64 Decoding <---------< */
        else if(dec_flag) {
            if(file_flag){
                using namespace termcolor;
                if(!file_data.second){
                    std::cout << red << bold << underline << file_data.first << reset << std::endl; 
                    return -1;
                }
                output_value = CONVERT::base64_decode(file_data.first);
                if (!output_option.empty()){
                  std::pair<std::string, bool> file_status = write_file(output_option, output_value, std::pair<std::string, std::string>("BASE64 DECODED BEGIN","BASE64 DECODED END"));
                  if (!file_status.second){ 
                    std::cout << red << bold << underline << file_status.first << reset << std::endl;
                    fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("BASE64 DECODED BEGIN"), std::string("BASE64 DECODED END")));
                    return -1;
                  }
                  std::cout << green << bold << underline << file_status.first << reset << std::endl;
                  return 0;
                }
                fmt::print("Base64({}): {}\n", input_option, fmt::format(fg(fmt::color::light_green), "{}", output_value)); 
                return 0;
            }
            output_value = CONVERT::base64_decode(input_option);
            if (!output_option.empty()){
                using namespace termcolor;
                std::pair<std::string, bool> file_status = write_file(output_option, output_value, std::pair<std::string, std::string>("BASE64 DECODED BEGIN","BASE64 DECODED END"));
                if (!file_status.second){ 
                  std::cout << red << bold << underline << file_status.first << reset << std::endl;
                  fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("BASE64 DECODED BEGIN"), std::string("BASE64 DECODED END")));
                  return -1;
                }
                std::cout << green << bold << underline << file_status.first << reset << std::endl;
                return 0;
            }
            fmt::print("Base64: {}\n", fmt::format(fg(fmt::color::light_green), "{}", output_value));
            return 0;
        }
        /* >---------> Base64 Requirements <---------< */
        else {
            fmt::print("--encode,-e OR --decode,-d flag is required\n");
            return -1;
        }
    }
    
    /* >---------> Caesar <---------< */
    else if(caesar_flag){
        /* >---------> Caesar Encoding/Decoding <---------< */
        if(file_flag){
            using namespace termcolor;
            if(!file_data.second){
                std::cout << red << bold << underline << file_data.first << reset << std::endl; 
                return -1;
            }
            output_value = CONVERT::caesar(file_data.first, caesar_shift);
            if (!output_option.empty()){
              std::pair<std::string, bool> file_status = write_file(output_option, output_value, std::pair<std::string, std::string>("CAESAR BEGIN","CAESAR END"));
              if (!file_status.second){ 
                std::cout << red << bold << underline << file_status.first << reset << std::endl;
                fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("CAESAR BEGIN"), std::string("CAESAR END")));
                return -1;
              }
              std::cout << green << bold << underline << file_status.first << reset << std::endl;
              return 0;
            }
            fmt::print("Caesar({}): {}\n\n", input_option, fmt::format(fg(fmt::color::light_green), "{}", output_value));
            return 0;
        }
        output_value = CONVERT::caesar(input_option, caesar_shift);
        if (!output_option.empty()){
            using namespace termcolor;
            std::pair<std::string, bool> file_status = write_file(output_option, output_value, std::pair<std::string, std::string>("CAESAR BEGIN","CAESAR END"));
            if (!file_status.second){ 
              std::cout << red << bold << underline << file_status.first << reset << std::endl;
              fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("CAESAR BEGIN"), std::string("CAESAR END")));
              return -1;
            }
            std::cout << green << bold << underline << file_status.first << reset << std::endl;
            return 0;
        }
        fmt::print("Caesar: {}\n\n", fmt::format(fg(fmt::color::light_green), "{}", output_value));
        return 0;
    }
    
    /* >---------> Format Requirements <---------< */
    else {
        fmt::print("No format specified, for more details try: convert --help\n");
        format_not_specified();
        return -1;
    }
  }

  /* >=========> dgst command actions <=========< */
  else if(dgst_command->parsed()){
    std::pair<std::string, bool> file_data = read_file(dgst_input_option); // => Stores the content of pathed file
    
    /* >---------> MD5 <---------< */
    if(md5_flag){
        if(dsgt_file_flag){
            using namespace termcolor;
            if(!file_data.second) {
                std::cout << red << bold << underline << file_data.first << reset << std::endl; 
                return -1;
            }
            output_value = md5::MD5()(file_data.first);
            if (!dgst_output_option.empty()){
              std::pair<std::string, bool> file_status = write_file(dgst_output_option, output_value, std::pair<std::string, std::string>("MD5 BEGIN","MD5 END"));
              if (!file_status.second){ 
                std::cout << red << bold << underline << file_status.first << reset << std::endl;
                fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("MD5 BEGIN"), std::string("MD5 END")));
                return -1;
              }
              std::cout << green << bold << underline << file_status.first << reset << std::endl;
              return 0;
            }
            fmt::print("md5({}): {}\n\n", dgst_input_option, fmt::format(fg(fmt::color::light_green), "{}", output_value));
            return 0;
        } 
        output_value = md5::MD5()(dgst_input_option);
        if (!dgst_output_option.empty()){
          using namespace termcolor;
          std::pair<std::string, bool> file_status = write_file(dgst_output_option, output_value, std::pair<std::string, std::string>("MD5 BEGIN","MD5 END"));
          if (!file_status.second){ 
            std::cout << red << bold << underline << file_status.first << reset << std::endl;
            fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("MD5 BEGIN"), std::string("MD5 END")));
            return -1;
          }
          std::cout << green << bold << underline << file_status.first << reset << std::endl;
          return 0;
        }
        fmt::print("md5: {}\n\n", fmt::format(fg(fmt::color::light_green), "{}", output_value));
        return 0;
    }
    
    /* >---------> SHA1 <---------< */
    else if(sha1_flag){
        if(dsgt_file_flag){
            using namespace termcolor;
            if(!file_data.second) {
                std::cout << red << bold << underline << file_data.first << reset << std::endl; 
                return -1;
            }
            output_value = sha1::SHA1()(file_data.first);
            if (!dgst_output_option.empty()){
              std::pair<std::string, bool> file_status = write_file(dgst_output_option, output_value, std::pair<std::string, std::string>("SHA1 BEGIN","SHA1 END"));
              if (!file_status.second){ 
                std::cout << red << bold << underline << file_status.first << reset << std::endl;
                fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("SHA1 BEGIN"), std::string("SHA1 END")));
                return -1;
              }
              std::cout << green << bold << underline << file_status.first << reset << std::endl;
              return 0;
            }
            fmt::print("sha1({}): {}\n\n", dgst_input_option, fmt::format(fg(fmt::color::light_green), "{}", output_value));
            return 0;
        } 
        output_value = sha1::SHA1()(dgst_input_option);
        if (!dgst_output_option.empty()){
          using namespace termcolor;
          std::pair<std::string, bool> file_status = write_file(dgst_output_option, output_value, std::pair<std::string, std::string>("SHA1 BEGIN","SHA1 END"));
          if (!file_status.second){ 
            std::cout << red << bold << underline << file_status.first << reset << std::endl;
            fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("SHA1 BEGIN"), std::string("SHA1 END")));
            return -1;
          }
          std::cout << green << bold << underline << file_status.first << reset << std::endl;
          return 0;
        }
        fmt::print("sha1: {}\n\n", fmt::format(fg(fmt::color::light_green), "{}", output_value));
        return 0;
    }
    
    /* >---------> SHA3 <---------< */
    else if(sha3_flag){
        if(dsgt_file_flag){
            using namespace termcolor;
            if(!file_data.second) {
                std::cout << red << bold << underline << file_data.first << reset << std::endl; 
                return -1;
            }
            output_value = sha3::SHA3()(file_data.first);
            if (!dgst_output_option.empty()){
              std::pair<std::string, bool> file_status = write_file(dgst_output_option, output_value, std::pair<std::string, std::string>("SHA3 BEGIN","SHA3 END"));
              if (!file_status.second){ 
                std::cout << red << bold << underline << file_status.first << reset << std::endl;
                fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("SHA3 BEGIN"), std::string("SHA3 END")));
                return -1;
              }
              std::cout << green << bold << underline << file_status.first << reset << std::endl;
              return 0;
            }
            fmt::print("sha3({}): {}\n\n", dgst_input_option, fmt::format(fg(fmt::color::light_green), "{}", output_value));
            return 0;
        } 
        output_value = sha3::SHA3()(dgst_input_option);
        if (!dgst_output_option.empty()){
          using namespace termcolor;
          std::pair<std::string, bool> file_status = write_file(dgst_output_option, output_value, std::pair<std::string, std::string>("SHA3 BEGIN","SHA3 END"));
          if (!file_status.second){ 
            std::cout << red << bold << underline << file_status.first << reset << std::endl;
            fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("SHA3 BEGIN"), std::string("SHA3 END")));
            return -1;
          }
          std::cout << green << bold << underline << file_status.first << reset << std::endl;
          return 0;
        }
        fmt::print("sha3: {}\n\n", fmt::format(fg(fmt::color::light_green), "{}", output_value));
        return 0;
    }
    
    /* >---------> SHA256 <---------< */
    else if(sha256_flag){
        if(dsgt_file_flag){
            using namespace termcolor;
            if(!file_data.second) {
                std::cout << red << bold << underline << file_data.first << reset << std::endl; 
                return -1;
            }
            output_value = sha256::SHA256()(file_data.first);
            if (!dgst_output_option.empty()){
              std::pair<std::string, bool> file_status = write_file(dgst_output_option, output_value, std::pair<std::string, std::string>("SHA256 BEGIN","SHA256 END"));
              if (!file_status.second){ 
                std::cout << red << bold << underline << file_status.first << reset << std::endl;
                fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("SHA256 BEGIN"), std::string("SHA256 END")));
                return -1;
              }
              std::cout << green << bold << underline << file_status.first << reset << std::endl;
              return 0;
            }
            fmt::print("sha256({}): {}\n\n", dgst_input_option, fmt::format(fg(fmt::color::light_green), "{}", output_value));
            return 0;
        } 
        output_value = sha256::SHA256()(dgst_input_option);
        if (!dgst_output_option.empty()){
          using namespace termcolor;
          std::pair<std::string, bool> file_status = write_file(dgst_output_option, output_value, std::pair<std::string, std::string>("SHA256 BEGIN","SHA256 END"));
          if (!file_status.second){ 
            std::cout << red << bold << underline << file_status.first << reset << std::endl;
            fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("SHA256 BEGIN"), std::string("SHA256 END")));
            return -1;
          }
          std::cout << green << bold << underline << file_status.first << reset << std::endl;
          return 0;
        }
        fmt::print("sha256: {}\n\n", fmt::format(fg(fmt::color::light_green), "{}", output_value));
        return 0;
    }
    
    /* >---------> CRC32 <---------< */
    else if(crc32_flag){
        if(dsgt_file_flag){
            using namespace termcolor;
            if(!file_data.second) {
                std::cout << red << bold << underline << file_data.first << reset << std::endl; 
                return -1;
            }
            output_value = crc32::CRC32()(file_data.first);
            if (!dgst_output_option.empty()){
              std::pair<std::string, bool> file_status = write_file(dgst_output_option, output_value, std::pair<std::string, std::string>("CRC32 BEGIN","CRC32 END"));
              if (!file_status.second){ 
                std::cout << red << bold << underline << file_status.first << reset << std::endl;
                fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("CRC32 BEGIN"), std::string("CRC32 END")));
                return -1;
              }
              std::cout << green << bold << underline << file_status.first << reset << std::endl;
              return 0;
            }
            fmt::print("crc32({}): {}\n\n", dgst_input_option, fmt::format(fg(fmt::color::light_green), "{}", output_value));
            return 0;
        } 
        output_value = crc32::CRC32()(dgst_input_option);
        if (!dgst_output_option.empty()){
          using namespace termcolor;
          std::pair<std::string, bool> file_status = write_file(dgst_output_option, output_value, std::pair<std::string, std::string>("CRC32 BEGIN","CRC32 END"));
          if (!file_status.second){ 
            std::cout << red << bold << underline << file_status.first << reset << std::endl;
            fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("CRC32 BEGIN"), std::string("CRC32 END")));
            return -1;
          }
          std::cout << green << bold << underline << file_status.first << reset << std::endl;
          return 0;
        }
        fmt::print("crc32: {}\n\n", fmt::format(fg(fmt::color::light_green), "{}", output_value));
        return 0;
    }
    
    /* >---------> Keccak <---------< */
    else if(keccak_flag){
        if(dsgt_file_flag){
            using namespace termcolor;
            if(!file_data.second) {
                std::cout << red << bold << underline << file_data.first << reset << std::endl; 
                return -1;
            }
            output_value = keccak::Keccak()(file_data.first);
            if (!dgst_output_option.empty()){
              std::pair<std::string, bool> file_status = write_file(dgst_output_option, output_value, std::pair<std::string, std::string>("KECCAK BEGIN","KECCAK END"));
              if (!file_status.second){ 
                std::cout << red << bold << underline << file_status.first << reset << std::endl;
                fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("KECCAK BEGIN"), std::string("KECCAK END")));
                return -1;
              }
              std::cout << green << bold << underline << file_status.first << reset << std::endl;
              return 0;
            }
            fmt::print("keccak({}): {}\n\n", dgst_input_option, fmt::format(fg(fmt::color::light_green), "{}", output_value));
            return 0;
        } 
        output_value = keccak::Keccak()(dgst_input_option);
        if (!dgst_output_option.empty()){
          using namespace termcolor;
          std::pair<std::string, bool> file_status = write_file(dgst_output_option, output_value, std::pair<std::string, std::string>("KECCAK BEGIN","KECCAK END"));
          if (!file_status.second){ 
            std::cout << red << bold << underline << file_status.first << reset << std::endl;
            fmt::println("\n{}\n",BorderFormatter::format(output_value, 50, '=', std::string("KECCAK BEGIN"), std::string("KECCAK END")));
            return -1;
          }
          std::cout << green << bold << underline << file_status.first << reset << std::endl;
          return 0;
        }
        fmt::print("keccak: {}\n\n", fmt::format(fg(fmt::color::light_green), "{}", output_value));
        return 0;
    }
    
    /* >---------> HASH Requirements <---------< */
    else {
        fmt::print("No HASH algorithm specified, for more details try: dgst --help\n");
        hash_not_specified();
        return -1;
    }
  } 
  /* >=========> Other subcommands Requirements <=========< */
  else {
    using namespace termcolor;
    std::cout << red << bold << "No [COMMAND]/[OPTION] specified, for more details try:" << reset << " enc --help\n" << reset << std::endl;
    return -1;
  }
  return 0;
}
