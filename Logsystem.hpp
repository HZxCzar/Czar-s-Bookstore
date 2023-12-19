#ifndef _LOGSYSTEM_HPP
#define _LOGSYSTEM_HPP
#include "database.hpp"
#include "Tool.hpp"
#include <bits/types/time_t.h>
#include <cstddef>
#include <string>
#include <ctime>
struct LogData{
    long long seq;
    long double in;
    long double out;
    bool operator<(const LogData& rhs)const;
    bool operator>(const LogData& rhs)const;
    bool operator==(const LogData &)const{return false;};
    void print()const{std::cout<<"in:"<<in<<"out:"<<out<<'\n';return;}
};

struct WorkerData{
    char time[80]={};
    char ID[30]={};
    char stmt[333]={};
    bool operator<(const WorkerData& rhs)const;
    bool operator>(const WorkerData& rhs)const;
    bool operator==(const WorkerData &)const;
    void print()const;
};

class Logsystem{
    friend class database<LogData>;
    public:
    Logsystem(const string& keyname=LOGKEY,const string& valuename=LOGVAL,const string& keynameworker=WORKERKEY,const string& valuenameworker=WORKERVAL);
    void IN(const long double& input);
    void WORKER(const string& ID,const string& stmt);
    void OUT(const long double& input);
    void ShowFinance(const string& input);
    void ReportWorker(const string& ID="");
    void Log();
    private:
    database<LogData> logdatabase;
    database<WorkerData> workerdatabase;
};
#endif