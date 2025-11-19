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
  CLI::Option* dgst_input_op = dgst_command->add_option("--input,-i", input_option, "Accept a value (-i <value> or --input=<value>)");
  dgst_command->add_option("--output,-o", output_option, "Generate the output in a desired file (-o <file> or --output=<file>)")->needs(dgst_input_op);

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
  
  /* >---------> convert command actions <---------< */
  if(convert_command->parsed()){
    if(!file_flag){
      if(binary_flag){
        if(enc_flag) fmt::print("Binary: {}\n\n", fmt::format(fg(fmt::color::light_green), "{}", CONVERT::binary_encode(input_option)));
        else if(dec_flag) fmt::print("Binary: {}\n", fmt::format(fg(fmt::color::light_green), "{}", CONVERT::binary_decode(input_option))); // Fixed: should be decode
        else fmt::print("--encode,-e OR --decode,-d flag is required\n");
      }
      else if(hex_flag){
        if(enc_flag) fmt::print("Hex: {}\n\n",fmt::format(fg(fmt::color::light_green), "{}", CONVERT::hex_encode(input_option)));
        else if(dec_flag) fmt::print("Hex: {}\n",fmt::format(fg(fmt::color::light_green), "{}", CONVERT::hex_decode(input_option)));
        else fmt::print("--encode,-e OR --decode,-d flag is required\n");
      }
      else if(base32_flag){
        if(enc_flag) fmt::print("Base32: {}\n\n", fmt::format(fg(fmt::color::light_green), "{}", CONVERT::base32_encode(input_option)));
        else if(dec_flag) fmt::print("Base32: {}\n", fmt::format(fg(fmt::color::light_green), "{}", CONVERT::base32_decode(input_option)));
        else fmt::print("--encode,-e OR --decode,-d flag is required\n");
      }
      else if(base64_flag){
        if(enc_flag) fmt::print("Base64: {}\n\n", fmt::format(fg(fmt::color::light_green), "{}", CONVERT::base64_encode(input_option)));
        else if(dec_flag) fmt::print("Base64: {}\n", fmt::format(fg(fmt::color::light_green), "{}", CONVERT::base64_decode(input_option)));
        else fmt::print("--encode,-e OR --decode,-d flag is required\n");
      }
      else if(caesar_flag){
        fmt::print("Caesar: {}\n\n", fmt::format(fg(fmt::color::light_green), "{}", CONVERT::caesar(input_option, caesar_shift)));
      }
      else {
        fmt::print("No format specified, for more details try: convert --help\n");
        format_not_specified();
      }
    }
    else {
      using namespace termcolor;
      std::cout << yellow << bold << underline << "File formating is not availabe at this time!" << reset << std::endl;
      return -1;
    }
  }

  else if(dgst_command->parsed()){
    if(!dsgt_file_flag){
      if(md5_flag){
        fmt::print("md5: {}\n\n", fmt::format(fg(fmt::color::light_green), "{}", md5::MD5()(dgst_input_option)));
      }
      else if(sha1_flag){
        fmt::print("sha1: {}\n\n", fmt::format(fg(fmt::color::light_green), "{}", sha1::SHA1()(dgst_input_option)));
      }
      else if(sha3_flag){
        fmt::print("sha3: {}\n\n", fmt::format(fg(fmt::color::light_green), "{}", sha3::SHA3()(dgst_input_option)));
      }
      else if(sha256_flag){
        fmt::print("sha256: {}\n\n", fmt::format(fg(fmt::color::light_green), "{}", sha256::SHA256()(dgst_input_option)));
      }
      else if(crc32_flag){
        fmt::print("crc32: {}\n\n", fmt::format(fg(fmt::color::light_green), "{}", crc32::CRC32()(dgst_input_option)));
      }
      else if(keccak_flag){
        fmt::print("keccak: {}\n\n", fmt::format(fg(fmt::color::light_green), "{}", keccak::Keccak()(dgst_input_option)));
      }
      else {
        fmt::print("No HASH algorithm specified, for more details try: dgst --help\n");
        hash_not_specified();
      }
    }
    else {
      using namespace termcolor;
      std::cout << yellow << bold << underline << "File hashing is not availabe at this time!" << reset << std::endl;
      return -1;

    }
  }
  else {
    using namespace termcolor;
    std::cout << red << bold << "No [COMMAND]/[OPTION] specified, for more details try:" << reset << " enc --help\n" << reset << std::endl;
    return -1;
  }
  return 0;
}
