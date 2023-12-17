#include "Tool.hpp"
#include <cctype>
#include <cstddef>
#include <string>

inline void TokenScanner::SetInput(const string &inp) {
  line = inp;
  pos = 0;
  len = line.size();
}

inline bool TokenScanner::ALLASCILL(const string &str) {
  for (int i = 0; i < str.size(); i++) {
    if (!ISASCLL(str[i])) {
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
inline string TokenScanner::NextISBN() {
  while (pos < len && line[pos] == ' ') {
    pos++;
  }
  int n1 = pos;
  while (pos < len && line[pos] != ' ') {
    pos++;
  }
  return line.substr(n1, pos - n1);
}

inline string TokenScanner::NextTokenNIC()
{
  while (pos < len && (line[pos] == ' ')) {
    pos++;
  }
  int n1 = pos;
  while (pos < len && line[pos] != ' '&& line[pos] != '=') {
    pos++;
  }
  return line.substr(n1, pos - n1);
}

inline string TokenScanner::NextToken() {
  while (pos < len && (line[pos] == ' ')) {
    pos++;
  }
  int n1 = pos;
  while (pos < len && line[pos] != ' ') {
    pos++;
  }
  return line.substr(n1, pos - n1);
}

inline string TokenScanner::NextKeyword() {
  while (pos < len &&
         (line[pos] == '\r' || line[pos] == ' ' || line[pos] == '\n' ||
          line[pos] == '\0' || line[pos] == '|')) {
    pos++;
  }
  int n1 = pos;
  while (pos < len && line[pos] != '|' && line[pos] != '\n' &&
         line[pos] != '\0' && line[pos] != ' ' && line[pos] != '\r') {
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

inline bool TokenScanner::ISUSERID() {
  bool judge = true;
  while (pos < len && (line[pos] == ' ')) {
    pos++;
  }
  if (pos == len) {
    return false;
  }
  long long p1 = pos;
  while (pos < len) {
    if (pos - p1 >= 30) {
      judge = false;
    }
    if (!std::isalnum(line[pos])) {
      if (line[pos] == ' ') {
        return judge;
      } else if (line[pos] != '_') {
        judge = false;
      }
    }
    pos++;
  }
  return judge;
}

inline bool TokenScanner::ISUSERNAME() {
  bool judge = true;
  while (pos < len && (line[pos] == ' ')) {
    pos++;
  }
  if (pos == len) {
    return false;
  }
  long long p1 = pos;
  //std::cout<<"HERE\n";
  while (pos < len) {
    if (pos - p1 >= 30) {
      judge = false;
    }
    if (line[pos] < 32 || line[pos] > 126) {
      judge = false;
    }
    if (line[pos] == ' ') {
      return judge;
    }
    pos++;
  }
  return judge;
}

inline bool TokenScanner::ISPRIVILEGE() {
  bool judge = true;
  while (pos < len && (line[pos] == ' ')) {
    pos++;
  }
  if (pos == len) {
    return false;
  }
  long long p1 = pos;
  while (pos < len) {
    if (pos - p1 >= 1) {
      judge = false;
    }
    if (line[pos] < '0' || line[pos] > '9') {
      judge = false;
    }
    if (line[pos] == ' ') {
      return judge;
    }
    pos++;
  }
  return judge;
}

inline bool TokenScanner::ISISBN() {
  bool judge = true;
  while (pos < len && (line[pos] == ' ')) {
    pos++;
  }
  if (pos == len) {
    return false;
  }
  long long p1 = pos;
  while (pos < len) {
    if (pos - p1 >= 20) {
      judge = false;
    }
    if (line[pos] < 32 || line[pos] > 126) {
      //std::cout<<"THIS:"<<line[pos]<<'\n';
      judge = false;
    }
    if (line[pos] == ' ') {
      return judge;
    }
    pos++;
  }
  return judge;
}

inline bool TokenScanner::ISNAME() {
  bool judge = true;
  while (pos < len && (line[pos] == ' ')) {
    pos++;
  }
  if (pos == len) {
    return false;
  }
  long long p1 = pos;
  while (pos < len) {
    if (pos - p1 >= 60) {
      judge = false;
    }
    if (line[pos] < 32 || line[pos] > 126) {
      judge = false;
    }
    if (line[pos] == '"') {
      judge = false;
    }
    if (line[pos] == ' ') {
      return judge;
    }
    pos++;
  }
  return judge;
}

inline bool TokenScanner::ISQUANTITY() {
  bool judge = true;
  while (pos < len && (line[pos] == ' ')) {
    pos++;
  }
  if (pos == len) {
    return false;
  }
  long long p1 = pos;
  while (pos < len) {
    if (pos - p1 >= 10) {
      judge = false;
    }
    if (line[pos] < '0' || line[pos] > '9') {
      judge = false;
    }
    if (line[pos] == ' ') {
      return judge;
    }
    pos++;
  }
  return judge;
}

inline bool TokenScanner::ISPRICE() {
  bool judge = true;
  while (pos < len && (line[pos] == ' ')) {
    pos++;
  }
  if (pos == len) {
    return false;
  }
  long long p1 = pos;
  long long p2 = 0;
  if (pos + 1 < len && line[pos] == '.') {
    judge = false;
  }
  while (pos < len) {
    if (pos - p1 >= 13) {
      judge = false;
    }
    if ((line[pos] < '0' || line[pos] > '9') && line[pos] != '.') {
      judge = false;
    }
    if (line[pos] == '.') {
      if (p2 != 0) {
        judge = false;
      }
      else
      {
        p2=pos;
      }
    }
    if (line[pos] == ' ') {
      return judge;
    }
    if (p2 != 0 && pos - p2 > 2) {
      judge = false;
    }
    pos++;
  }
  return judge;
}

inline bool TokenScanner::ISKEYWORD()
{
  bool judge = true;
  while (pos < len && (line[pos] == ' ')) {
    pos++;
  }
  if (pos == len) {
    return false;
  }
  long long p1 = pos;
  bool listlen=false;
  while (pos < len) {
    if (pos - p1 >= 60) {
      judge = false;
    }
    if (line[pos] < 32 || line[pos] > 126) {
      judge = false;
    }
    if (line[pos] == '"') {
      judge = false;
    }
    if(line[pos]=='|'&&listlen==true)
    {
      judge=false;
    }
    if(line[pos]=='|')
    {
      listlen=true;
    }
    if(line[pos]!='|')
    {
      listlen=false;
    }
    if (line[pos] == ' ') {
      return judge;
    }
    pos++;
  }
  return judge;
}

inline bool TokenScanner::ISCOUNT() {
  bool judge = true;
  while (pos < len && (line[pos] == ' ')) {
    pos++;
  }
  if (pos == len) {
    return false;
  }
  long long p1 = pos;
  while (pos < len) {
    if (pos - p1 >= 10) {
      judge = false;
    }
    if (line[pos] < '0' || line[pos] > '9') {
      judge = false;
    }
    if (line[pos] == ' ') {
      return judge;
    }
    pos++;
  }
  return judge;
}