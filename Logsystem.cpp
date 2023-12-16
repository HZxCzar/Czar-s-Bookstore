#include "Logsystem.hpp"
#include "Tool.hpp"
#include "database.hpp"
#include <cstddef>
#include <iostream>
#include <iomanip>

inline Logsystem::Logsystem(const string &keyname, const string &valuename) {
  logdatabase.Set(keyname, valuename);
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

inline void Logsystem::IN(const long double &input) {
  LogData add;
  //std::cout << "INPUT:" << input;
  if (!logdatabase.empt) {
    add = logdatabase.Get(sizeof(long long), 0);
    add.seq++;
    //std::cout << add.seq << "<<\n";
  } else {
    add.seq = 0;
  }
  add.in = input;
  add.out = 0.00;
  // if(logdatabase.empt)
  // {
  //   std::cout<<"IN\n";
  // }
  logdatabase.ADD(add);
}

inline void Logsystem::OUT(const long double &input) {
  LogData add;
  if (!logdatabase.empt) {
    add = logdatabase.Get(sizeof(long long), 0);
  } else {
    add.seq = 0;
  }
  add.out = input;
  add.in = 0.00;
  add.seq++;
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
    num = add.seq+1;
    string token = tokenScanner.NextToken();
    tmpck.SetInput(token);
    if(!tmpck.ISCOUNT())
    {
      std::cout<<"Invalid\n";
      return;
    }
    size_t n = tokenScanner.StringToSizeT(token);
    //std::cout<<"num:"<<num<<" n:"<<n<<'\n';
    if(n>2147483647)
    {
      std::cout<<"Invalid\n";
      return;
    }
    basis.seq = num - n;
    if(n==0)
    {
      std::cout<<"\n";
      return;
    }
    if(basis.seq<0)
    {
      std::cout<<"Invalid\n";
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
  std::cout << "+ " <<std::fixed << std::setprecision(2) << get << " - " <<std::fixed << std::setprecision(2) << pay << '\n';
}