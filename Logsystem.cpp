#include "Logsystem.hpp"
#include "Tool.hpp"
#include "database.hpp"
#include <bits/types/time_t.h>
#include <cstddef>
#include <ctime>
#include <iomanip>
#include <iostream>

inline Logsystem::Logsystem(const string &keyname, const string &valuename,
                            const string &keynameworker,
                            const string &valuenameworker) {
  logdatabase.Set(keyname, valuename);
  workerdatabase.Set(keynameworker, valuenameworker);
}

inline bool LogData::operator<(const LogData &rhs) const {
  if (seq > rhs.seq) {
    return true;
  }
  return false;
}

inline bool LogData::operator>(const LogData &rhs) const {
  if (seq < rhs.seq) {
    return true;
  }
  return false;
}

inline bool WorkerData::operator<(const WorkerData &rhs) const {
  for (int i = 0; i < 30; i++) {
    if (ID[i] < rhs.ID[i]) {
      return true;
    }
    if (ID[i] > rhs.ID[i]) {
      return false;
    }
  }
  if (time < rhs.time) {
    return true;
  }
  return false;
}

inline bool WorkerData::operator>(const WorkerData &rhs) const {
  for (int i = 0; i < 30; i++) {
    if (ID[i] > rhs.ID[i]) {
      return true;
    }
    if (ID[i] < rhs.ID[i]) {
      return false;
    }
  }
  if (time > rhs.time) {
    return true;
  }
  return false;
}

inline bool WorkerData::operator==(const WorkerData &rhs) const {
  for (int i = 0; i < 30; i++) {
    if (ID[i] != rhs.ID[i]) {
      return false;
    }
  }
  return true;
}

inline void WorkerData::print() const {
  for (int i = 0; i < 30; i++) {
    if (ID[i] == '\0') {
      break;
    }
    std::cout << ID[i];
  }
  std::cout << '\t';
  std::cout << " | statement : " << stmt << '\t' << " | excute time : " << time
            << '\n';
}

inline void Logsystem::IN(const long double &input) {
  LogData add;
  if (!logdatabase.empt) {
    add = logdatabase.Get(sizeof(long long), 0);
    add.seq++;
  } else {
    add.seq = 0;
  }
  add.in = input;
  add.out = 0.00;
  logdatabase.ADD(add);
}

inline void Logsystem::OUT(const long double &input) {
  LogData add;
  if (!logdatabase.empt) {
    add = logdatabase.Get(sizeof(long long), 0);
    add.seq++;
  } else {
    add.seq = 0;
  }
  add.out = input;
  add.in = 0.00;
  logdatabase.ADD(add);
}

inline void Logsystem::ShowFinance(const string &input) {
  logdatabase.Set(LOGKEY, LOGVAL);
  TokenScanner tokenScanner;
  TokenScanner tmpck;
  tokenScanner.SetInput(input);
  LogData basis;
  long long p, pos;
  if (tokenScanner.hasMoreToken()) {
    long long num;
    LogData add;
    if (!logdatabase.empt) {
      add = logdatabase.Get(sizeof(long long), 0);
    } else {
      add.seq = 0;
    }
    num = add.seq + 1;
    string token = tokenScanner.NextToken();
    tmpck.SetInput(token);
    if (!tmpck.ISCOUNT()) {
      std::cout << "Invalid\n";
      return;
    }
    size_t n = tokenScanner.StringToSizeT(token);
    // std::cout<<"num:"<<num<<" n:"<<n<<'\n';
    if (n > 2147483647) {
      std::cout << "Invalid\n";
      return;
    }
    basis.seq = num - n;
    if (n == 0) {
      std::cout << "\n";
      return;
    }
    if (basis.seq < 0) {
      std::cout << "Invalid\n";
      return;
    }
  } else {
    basis.seq = 0;
  }
  logdatabase.Find(basis, p, pos);
  long double get = 0.00, pay = 0.00;
  long long ind = sizeof(long long);
  A<LogData> K;
  B<LogData> V;
  while (ind != p) {
    logdatabase.Afile.readA(K, ind);
    logdatabase.Bfile.readA(V, K.pos);
    for (long long i = 0; i < V.size; i++) {
      get += V.elem[i].in;
      pay += V.elem[i].out;
    }
    ind = K.next;
  }
  logdatabase.Afile.readA(K, ind);
  logdatabase.Bfile.readA(V, K.pos);
  for (long long i = 0; i <= pos; i++) {
    get += V.elem[i].in;
    pay += V.elem[i].out;
    // std::cout << "in:" << V.elem[i].in << "out:" << V.elem[i].out << '\n';
  }
  std::cout << "+ " << std::fixed << std::setprecision(2) << get << " - "
            << std::fixed << std::setprecision(2) << pay << '\n';
}

inline void Logsystem::WORKER(const string &ID, const string &stmt) {
  WorkerData add;
  Turn30(add.ID, ID);
  for (int i = 0; i < stmt.size(); i++) {
    add.stmt[i] = stmt[i];
  }
  time_t nowtime = time(0);
  std::tm *timeinfo = std::localtime(&nowtime);
  std::strftime(add.time, sizeof(add.time), "%Y-%m-%d %H:%M:%S", timeinfo);
  workerdatabase.ADD(add);
}

inline void Logsystem::ReportWorker(const string &input) {
  TokenScanner tokenscanner;
  tokenscanner.SetInput(input);
  if (!tokenscanner.hasMoreToken()) {
    std::cout << "Invalid\n";
    return;
  }
  string token = tokenscanner.NextToken();
  if (token != "worker") {
    std::cout << "Invalid\n";
    return;
  }
  if (!tokenscanner.hasMoreToken()) {
    workerdatabase.PRINT();
    return;
  } else {
    string ID = tokenscanner.NextToken();
    TokenScanner tmpck;
    tmpck.SetInput(ID);
    if (!tmpck.ISUSERID()) {
      std::cout << "Invalid\n";
      return;
    }
    WorkerData ins;
    Turn30(ins.ID, ID);
    long long beg, end;
    workerdatabase.FindRange(ins, beg, end);
    if (!workerdatabase.if_find) {
      std::cout << "\n";
      return;
    } else {
      long long ind = beg;
      bool out = false;
      while (ind != end) {
        long long start = workerdatabase.GetBound(ins, ind);
        long long tail = workerdatabase.GetUp(ins, ind);
        if (workerdatabase.if_find) {
          out = true;
          if (start > tail) {
            std::cout << "Wrong\n";
          }
          workerdatabase.PRINT(ind, ind, start, tail + 1);
        }
        ind = workerdatabase.GO(ind);
      }
      if (!out) {
        std::cout << '\n';
        return;
      }
    }
  }
}

inline void Logsystem::Log() { workerdatabase.PRINT(); }