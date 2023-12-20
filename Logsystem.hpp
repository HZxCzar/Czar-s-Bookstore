#ifndef _LOGSYSTEM_HPP
#define _LOGSYSTEM_HPP
#include "Tool.hpp"
#include "database.hpp"
#include <bits/types/time_t.h>
#include <cstddef>
#include <ctime>
#include <string>
struct LogData {
  long long seq;
  long double in;
  long double out;
  bool operator<(const LogData &rhs) const;
  bool operator>(const LogData &rhs) const;
  bool operator==(const LogData &) const { return false; };
  void print() const {
    std::cout << "in:" << in << "out:" << out << '\n';
    return;
  }
};

struct WorkerData {
  char time[80] = {};
  char ID[30] = {};
  char stmt[333] = {};
  bool operator<(const WorkerData &rhs) const;
  bool operator>(const WorkerData &rhs) const;
  bool operator==(const WorkerData &) const;
  void print() const;
};

struct BookFinance {
  char ISBN[20] = {};
  char time[80] = {};
  long double in = 0.00;
  long double out = 0.00;
  bool operator<(const BookFinance &rhs) const;
  bool operator>(const BookFinance &rhs) const;
  bool operator==(const BookFinance &rhs) const;
  void print() const;
};

class Logsystem {
  friend class database<LogData>;
  friend class database<WorkerData>;

public:
  Logsystem(const string &keyname = LOGKEY, const string &valuename = LOGVAL,
            const string &keynameworker = WORKERKEY,
            const string &valuenameworker = WORKERVAL,
            const string &keynamefinance = FINANCEKEY,
            const string &valuenamefinance = FINANCEVAL);
  void IN(const long double &input);
  void WORKER(const string &ID, const string &stmt);
  void OUT(const long double &input);
  void ShowFinance(const string &input);
  void ReportWorker(const string &ID = "");
  void UPD(const string &ISBN);
  void ReportFinance();
  void Log();

private:
  database<LogData> logdatabase;
  database<WorkerData> workerdatabase;
  database<BookFinance> financedatabase;
};
#endif