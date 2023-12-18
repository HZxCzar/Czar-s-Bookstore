#ifndef _LOGSYSTEM_HPP
#define _LOGSYSTEM_HPP
#include "database.hpp"
#include "Tool.hpp"
#include <cstddef>
#include <string>
struct LogData{
    long long seq;
    long double in;
    long double out;
    bool operator<(const LogData& rhs)const;
    bool operator>(const LogData& rhs)const;
    bool operator==(const LogData &)const{return false;};
    void print()const{std::cout<<"in:"<<in<<"out:"<<out<<'\n';return;}
};
class Logsystem{
    friend class database<LogData>;
    public:
    Logsystem(const string& keyname=LOGKEY,const string& valuename=LOGVAL);
    void IN(const long double& input);
    void OUT(const long double& input);
    void ShowFinance(const string& input);
    private:
    //long long num=0;
    database<LogData> logdatabase;
};
#endif