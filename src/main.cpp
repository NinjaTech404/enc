#include<CLI/CLI.hpp> // The CLI Generator
#include<fmt/core.h>
#include<fmt/color.h>
#include<termcolor/termcolor.hpp>
#include<vector>
#include<string>
#include<iostream>
#include<convert/convert.hpp>
#include<hash_library/md5.h>
#include<hash_library/md5.cpp>
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
  convert_command->add_option("--input,-i", input_option, "Accept a value (-i <value> or --input=<value>)")->required();
  convert_command->add_option("--output,-o", output_option, "Generate the output in a desired file (-o <file> or --output=<file>)");
  CLI::Option* caesar_option = convert_command->add_option("--shift,-s", caesar_shift, "Specify the shift number for caesar cipher");

  // ==> convert flags
  bool file_flag(0), binary_flag(0), hex_flag(0), base32_flag(0), base64_flag(0), caesar_flag(0), enc_flag(0), dec_flag;
  CLI::Option* file_f = convert_command->add_flag("--file,-f", file_flag, "Accept the input value as a file name");
  CLI::Option* binary_f = convert_command->add_flag("--binary", binary_flag, "Convert into binary");
  CLI::Option* hex_f = convert_command->add_flag("--hex", hex_flag, "Convert into hexadecimal");
  CLI::Option* base32_f = convert_command->add_flag("--base32", base32_flag, "Convert into base32");
  CLI::Option* base64_f = convert_command->add_flag("--base64", base64_flag, "Convert into base64");
  CLI::Option* caesar_f = convert_command->add_flag("--caesar", caesar_flag, "Apply caesar cipher");
  CLI::Option* enc_f = convert_command->add_flag("--encode, -e", enc_flag, "to encode the value to the specified format");
  CLI::Option* dec_f = convert_command->add_flag("--decode, -d", dec_flag, "to decode the value from the specified format");

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

  // ==> dgst flags 
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
        fmt::print("No format specified, for more details try: convert -h\n");
        format_not_specified();
      }
    }
    else {
      using namespace termcolor;
      std::cout << yellow << bold << underline << "File formating is not availabe at this time" << reset << std::endl;
      return -1;
    }
  }

  if(dgst_command->parsed()){
    using namespace termcolor;
    std::cout << yellow << bold << underline << "File formating is not availabe at this time" << reset << std::endl;
    return -1;
     
  }
  return 0;
}
