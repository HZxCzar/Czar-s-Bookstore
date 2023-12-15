#ifndef _LOGSYSTEM_HPP
#define _LOGSYSTEM_HPP
#include "database.hpp"
#include "Tool.hpp"
#include <cstddef>
#include <string>
struct LogData{
    long long seq;
    double in;
    double out;
    bool operator<(const LogData& rhs)const;
    bool operator>(const LogData& rhs)const;
    void print()const{std::cout<<"in:"<<in<<"out:"<<out<<'\n';return;}
};
class Logsystem{
    friend class database<LogData>;
    public:
    Logsystem(const string& keyname=LOGKEY,const string& valuename=LOGVAL);
    void IN(const double& input);
    void OUT(const double& input);
    void ShowFinance(const string& input);
    private:
    //long long num=0;
    database<LogData> logdatabase;
};
#endif