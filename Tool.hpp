#ifndef _TOOL_HPP
#define _TOOL_HPP
#include <cctype>
#include <cstddef>
#include<iostream>
#include <string>
#include <cstring>
using std::string;
class TokenScanner{
    public:
    TokenScanner()=default;
    void SetInput(const string& inp);
    bool hasMoreToken();
    std::string NextToken();
    std::string NextKeyword();
    size_t StringToSizeT(const string& str);
    double StringToDouble(const string& str);
    string BehindToken();
    bool ISDIGIT(const string& str);
    bool ALLASCILL(const string& str);
    private:
    string line;
    int pos=0;
    int len=0;
};
inline void Turn60(char (&t)[60],const string& targ)
{
    memset(t, 0, 60);
    for(int i=0;i<targ.size();i++)
    {
        t[i]=targ[i];
    }
}

inline void Turn20(char (&t)[20],const string& targ)
{
    memset(t, 0, 20);
    for(int i=0;i<targ.size();i++)
    {
        t[i]=targ[i];
    }
}

inline void Turn30(char (&t)[30],const string& targ)
{
    memset(t, 0, 30);
    for(int i=0;i<targ.size();i++)
    {
        t[i]=targ[i];
    }
}

inline bool ISASCLL(const char& tmp)
{
    return (tmp>=0 && tmp<=127);
}
#endif