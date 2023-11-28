#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H
struct Options
{
  unsigned int padding;
  unsigned long hexadecimal;
};
struct Errors
{
  std::map<int, std::string> messages;
};
namespace Globals
{
  extern unsigned int UINT_MAX_ENSURE;
  bool IsHexadecimalString(const std::string& string);
  bool IsUINTString(const std::string& string);
  void StripHexadecimalPrefix(std::string& string);
  void StringReplace(std::string& haystack, const std::string& needle, const std::string& replace);
}
#endif // ! GLOBALS_H