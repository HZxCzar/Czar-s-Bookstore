#include "Tool.hpp"
#include <cstddef>
#include <string>

inline void TokenScanner::SetInput(const string &inp) {
  line = inp;
  pos = 0;
  len = line.size();
}

inline bool TokenScanner::ALLASCILL(const string &str)
{
  for(int i=0;i<str.size();i++)
  {
    if(!ISASCLL(str[i]))
    {
      return false;
    }
  }
  return true;
}

inline bool TokenScanner::ISDIGIT(const string &str) {
  for (int i = 0; i < str.size(); i++) {
    if (str[i] > '9' || str[i] < '0') {
      return false;
    }
  }
  return true;
}

inline bool TokenScanner::hasMoreToken() {
  bool flag = false;
  for (int i = pos; i < len; i++) {
    if (line[i] != '\n' && line[i] != '\r' && line[i] != ' ' &&
        line[i] != '\0' && line[i] != '|' && line[i] != '"') {
      flag = true;
      break;
    }
  }
  return flag;
}

inline string TokenScanner::NextToken() {
  while (pos < len &&
         (line[pos] == '\r' || line[pos] == ' ' || line[pos] == '\n' ||
          line[pos] == '\0' || line[pos] == '=' || line[pos] == '"')) {
    pos++;
  }
  int n1 = pos;
  while (pos < len && line[pos] != ' ' && line[pos] != '\n' &&
         line[pos] != '\0' && line[pos] != '=' && line[pos] != '"' &&
         line[pos] != '\r') {
    pos++;
  }
  return line.substr(n1, pos - n1);
}

inline string TokenScanner::NextKeyword() {
  while (pos < len &&
         (line[pos] == '\r' || line[pos] == ' ' || line[pos] == '\n' ||
          line[pos] == '\0' || line[pos] == '=' || line[pos] == '|' ||
          line[pos] == '"')) {
    pos++;
  }
  int n1 = pos;
  while (pos < len && line[pos] != '|' && line[pos] != '\n' &&
         line[pos] != '\0' && line[pos] != '=' && line[pos] != ' ' &&
         line[pos] != '"' && line[pos] != '\r') {
    pos++;
  }
  return line.substr(n1, pos - n1);
}

inline string TokenScanner::BehindToken() { return line.substr(pos); }

inline size_t TokenScanner::StringToSizeT(const string &str) {
  int l = str.length();
  size_t ret = 0;
  for (int i = 0; i < l; i++) {
    ret = ret * 10 + (str[i] - '0');
  }
  return ret;
}

inline double TokenScanner::StringToDouble(const string &str) {
  int l = str.length();
  double ret = 0.00;
  int i;
  for (i = 0; i < l; i++) {
    if (str[i] == '.') {
      break;
    }
    ret = ret * 10.00 + (str[i] - '0') * 1.00;
  }
  double base = 10.00;
  for (i = i + 1; i < l; i++) {
    ret += (str[i] - '0') / base;
    base *= 10.00;
  }
  return ret;
}