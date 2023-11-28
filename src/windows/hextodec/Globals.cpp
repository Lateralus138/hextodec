#include "stdafx.h"
#include "Globals.h"
extern struct Options options;
extern struct Errors errors;
namespace Globals
{
  unsigned int UINT_MAX_ENSURE = (unsigned int) - 1;
  bool IsHexadecimalString(const std::string& string)
  {
    std::string string_ = string;
    StripHexadecimalPrefix(string_);
    if (string_.empty()) return false;
    return (string_.find_first_not_of("0123456789abcdefABCDEF", 0) == std::string::npos);
  }
  bool IsUINTString(const std::string& string)
  {
    return (string.find_first_not_of("0123456789") == std::string::npos);
  }
  void StripHexadecimalPrefix(std::string& string)
  {
    StringReplace(string, "#", "");
    StringReplace(string, "0x", "");
  }
  void StringReplace(std::string& haystack, const std::string& needle, const std::string& replace)
  {
    size_t position = 0;
    while ((position = haystack.find(needle, position)) != std::string::npos)
    {
      haystack.replace(position, needle.size(), replace);
      position += replace.size();
    }
  }
}