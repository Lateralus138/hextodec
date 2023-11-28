#pragma once
class ArgumentParser
{
private:
  std::vector<std::string> tokens;
public:
  ArgumentParser(int& argc, const char** argv, int start);
  const std::vector<std::string>& getArgs() const;
  bool optionExists(const std::string& option) const;
  template <typename UnaryPredicate>
  bool optionExistsByPredicate(UnaryPredicate predicate)
  {
    std::vector<std::string>::iterator iterator =
      std::find_if(this->tokens.begin(), this->tokens.end(), predicate);
    return (iterator != this->tokens.end());
  }
  bool optionsExist(const std::vector<std::string>& options) const;
  const std::string& getOption(const std::string& option) const;
  const std::string& getOptions(const std::vector<std::string>& options) const;
  template <typename UnaryPredicate>
  const std::string getOptionByPredicate(UnaryPredicate predicate)
  {
    std::string value = std::string("");
    std::vector<std::string>::iterator iterator =
      std::find_if(this->tokens.begin(), this->tokens.end(), predicate);
    if (iterator != this->tokens.end())
    {
      value = std::string(*iterator);
    }
    static const std::string RESULT = value;
    return RESULT;
  }
};

