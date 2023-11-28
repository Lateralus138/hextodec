// ╔═════════════════════════════════════════════════════════════════════════╗
// ║ Hexadecimal To Decimal - Convert hexadecimal value to an integer value  ║
// ║ © 2023 Ian Pride - New Pride Software / Services                        ║
// ╚═════════════════════════════════════════════════════════════════════════╝
#include "pch.h"
int ParseArguments(ArgumentParser& args, Options &options)
{
  std::vector<std::string> HELPOPTS = {"-h", "--help", "-H", "--HELP"};
  std::vector<std::string> HEXAOPTS = { "-x", "--hexadecimal", "-X", "--HEXADECIMAL" };
  std::vector<std::string> PADDOPTS = {"-p", "--padding", "-P", "--PADDING" };
  if (args.optionsExist(HELPOPTS))
  {
    std::string message =
      "\n  Hexadecimal To Decimal - Convert hexadecimal values to decimal format."
      "\n  hextodec [OPTIONS [VALUES]]"
      "\n\n  @OPTIONS"
      "\n    -h, --help        This help message."
      "\n    -x, --hexadecimal The HEXADECIMAL number to convert."
      "\n    -p, --padding     DECIMAL number of 0's to prepend to the result."
      "\n\n  @VALUES"
      "\n    HEXADECIMAL       Base 16 value; [0-9a-f]"
      "\n    DECIMAL           Base 10 value; [0-9]"
      "\n\n";
    std::cout << message;
    return -1;
  }
  if (args.optionsExist(HEXAOPTS))
  {
    std::string option = args.getOptions(HEXAOPTS);
    if (option.empty()) return 2;
    const bool ISHEXA = Globals::IsHexadecimalString(option);
    if (!ISHEXA) return 3;
    Globals::StripHexadecimalPrefix(option);
    unsigned long value{};
    try
    {
      value = std::stoul(option, nullptr, 16);
    }
    catch (std::out_of_range& ofr_error)
    {
      (void)ofr_error;
      return 4;
    }
    options.hexadecimal = value;
  }
  if (args.optionsExist(PADDOPTS))
  {
    const std::string option = args.getOptions(PADDOPTS);
    if (option.empty()) return 5;
    const bool ISUINT = Globals::IsUINTString(option);
    if (!ISUINT) return 6;
    options.padding = std::stoi(option);
  }
  return EXIT_SUCCESS;
}
int main(int argc, const char* argv[])
{
  Options options = {0, 0};
  Errors errors =
  {{
    {1, "Not enough arguments passed to the program."},
    {2, "No argument provided for [-x, --hexadecimal]."},
    {3, "Argument provided for [-x, --hexadecimal] is not a valid hexadecimal value."},
    {4, "Argument provided for [-x, --hexadecimal] exceeds that maximum unsigned integer limit."},
    {5, "No argument provided for [-p, --padding]."},
    {6, "Argument provided for [-p, --padding] is not a valid positive integer."}
  }};
  if (argc < 2)
  {
    std::cerr << errors.messages[1] << '\n';
    return 1;
  }
  ArgumentParser args(argc, argv, 1);
  const int PARSED = ParseArguments(args, options);
  if (PARSED == -1) return EXIT_SUCCESS;
  if (PARSED > 0)
  {
    std::cerr << errors.messages[PARSED] << '\n';
    return PARSED;
  }
  std::cout << std::setfill('0') << std::setw(options.padding) << options.hexadecimal << '\n';
  return EXIT_SUCCESS;
}
