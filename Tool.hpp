#ifndef _TOOL_HPP
#define _TOOL_HPP
#include <cctype>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <string>
using std::string;
class TokenScanner {
public:
  TokenScanner() = default;
  void SetInput(const string &inp);
  bool hasMoreToken();
  std::string NextToken();
  std::string NextKeyword();
  std::string NextISBN();
  std::string NextTokenNIC();
  string NextFollow();
  void AD(){pos++;}
  bool ISUSERID();
  bool ISUSERNAME();
  bool ISPRIVILEGE();
  bool ISISBN();
  bool ISNAME();
  bool ISQUANTITY();
  bool ISKEYWORD();
  bool ISONEKEYWORD();
  bool ISPRICE();
  bool ISCOUNT();
  size_t StringToSizeT(const string &str);
  double StringToDouble(const string &str);
  string BehindToken();
  bool ISDIGIT(const string &str);
  bool ALLASCILL(const string &str);

private:
  string line;
  int pos = 0;
  int len = 0;
};
inline void Turn60(char (&t)[60], const string &targ) {
  memset(t, 0, 60);
  for (int i = 0; i < targ.size(); i++) {
    t[i] = targ[i];
  }
}

inline void Turn20(char (&t)[20], const string &targ) {
  memset(t, 0, 20);
  for (int i = 0; i < targ.size(); i++) {
    t[i] = targ[i];
  }
}

inline void Turn30(char (&t)[30], const string &targ) {
  memset(t, 0, 30);
  for (int i = 0; i < targ.size(); i++) {
    t[i] = targ[i];
  }
}

inline string shr(const string& str)
{
  string ans;
  int l=0,r=str.size()-1;
  while(l<=r && str[l]==' ')
  {
    l++;
  }
  while(r>=l && str[r]==' ')
  {
    r--;
  }
  bool check=false;
  for(int i=l;i<=r;i++)
  {
    if(str[i]==' ')
    {
      if(check)
      {
        continue;
      }
      check=true;
    }
    else
    {
      check=false;
    }
    ans=ans+str[i];
  }
  return ans;
}

inline bool ISASCLL(const char &tmp) { return (tmp >= 32 && tmp <= 126); }
#endif