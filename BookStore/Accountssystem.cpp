#include "Accountssystem.hpp"
#include "Tool.hpp"
#include <cstring>
inline accountsystem::accountsystem(const string &keyname,
                                    const string &valuename) {
  accountdata.Set(keyname, valuename);
  Account BOOS;
  string name = "root", passwd = "sjtu";
  Turn30(BOOS.UserID, name);
  Turn30(BOOS.Password, passwd);
  BOOS.privilege = 7;
  accountdata.ADD(BOOS);
  LOG = false;
}

inline bool Account::operator<(const Account &rhs) const {
  for (long long i = 0; i < 30; i++) {
    if (UserID[i] < rhs.UserID[i]) {
      return true;
    } else if (UserID[i] > rhs.UserID[i]) {
      return false;
    }
  }
  return false;
}

inline bool Account::operator>(const Account &rhs) const {
  for (long long i = 0; i < 30; i++) {
    if (UserID[i] > rhs.UserID[i]) {
      return true;
    } else if (UserID[i] < rhs.UserID[i]) {
      return false;
    }
  }
  return false;
}

inline void accountsystem::Su(const string &input) {
  TokenScanner tokenScanner;
  tokenScanner.SetInput(input);
  if (!tokenScanner.hasMoreToken()) {
    std::cout << "Invalid\n";
    return;
  }
  string token = tokenScanner.NextToken();
  Account basis;
  Turn30(basis.UserID, token);
  long long p, pos;
  accountdata.Find(basis, p, pos);
  if (!accountdata.excute) {
    std::cout << "Invalid\n";
    return;
  }
  basis = accountdata.Get(p, pos);
  login person;
  person.ID = token;
  person.ifSelect = false;
  person.pri = basis.privilege;
  if (!tokenScanner.hasMoreToken() &&
      (!LOG || LoginStack.back().pri <= person.pri)) {
    std::cout << "Invalid\n";
    return;
  }
  if (tokenScanner.hasMoreToken()) {
    token = tokenScanner.NextToken();
    char check[30] = {};
    Turn30(check, token);
    if (std::memcmp(check, basis.Password, 30)) {
      std::cout << "Invalid\n";
      return;
    }
  }
  if (!LOG) {
    LOG = true;
  }
  LoginStack.push_back(person);
}

inline void accountsystem::Logout() {
  if (!LOG) {
    std::cout << "Invalid\n";
    return;
  }
  LoginStack.pop_back();
  if (LoginStack.size() == 0) {
    LOG = false;
  }
}

inline void accountsystem::Register(const string &input) {
  TokenScanner tokenScanner;
  tokenScanner.SetInput(input);
  if (!tokenScanner.hasMoreToken()) {
    std::cout << "Invalid\n";
    return;
  }
  string token = tokenScanner.NextToken();
  Account basis;
  Turn30(basis.UserID, token);
  long long p, pos;
  accountdata.Find(basis, p, pos);
  if (accountdata.excute) {
    std::cout << "Invalid\n";
    return;
  }
  if (!tokenScanner.hasMoreToken()) {
    std::cout << "Invalid\n";
    return;
  }
  token = tokenScanner.NextToken();
  Turn30(basis.Password, token);
  if (!tokenScanner.hasMoreToken()) {
    std::cout << "Invalid\n";
    return;
  }
  token = tokenScanner.NextToken();
  Turn30(basis.Username, token);
  basis.privilege = 1;
  accountdata.ADD(basis);
}

inline void accountsystem::Passwd(const string &input) {
  TokenScanner tokenScanner;
  tokenScanner.SetInput(input);
  if (!tokenScanner.hasMoreToken()) {
    std::cout << "Invalid\n";
    return;
  }
  string token = tokenScanner.NextToken();
  Account basis;
  Turn30(basis.UserID, token);
  long long p, pos;
  accountdata.Find(basis, p, pos);
  if (!accountdata.excute) {
    std::cout << "Invalid\n";
    return;
  }
  basis = accountdata.Get(p, pos);
  if (!tokenScanner.hasMoreToken()) {
    std::cout << "Invalid\n";
    return;
  }
  if (LoginStack.back().pri == 7) {
    string token1, token2;
    token1 = tokenScanner.NextToken();
    if (tokenScanner.hasMoreToken()) {
      token = tokenScanner.NextToken();
      char check[30] = {};
      Turn30(check, token1);
      if (std::memcmp(check, basis.Password, 30)) {
        std::cout << "Invalid\n";
        return;
      }
    } else {
      token = token1;
    }
  } else {
    token = tokenScanner.NextToken();
    char check[30] = {};
    Turn30(check, token);
    if (std::memcmp(check, basis.Password, 30)) {
      std::cout << "Invalid\n";
      return;
    }
    if (!tokenScanner.hasMoreToken()) {
      std::cout << "Invalid\n";
      return;
    }
    token = tokenScanner.NextToken();
  }
  Turn30(basis.Password, token);
  accountdata.Update(basis, p, pos);
}

inline void accountsystem::useradd(const string &input) {
  TokenScanner tokenScanner;
  tokenScanner.SetInput(input);
  if (!tokenScanner.hasMoreToken()) {
    std::cout << "Invalid\n";
    return;
  }
  string token = tokenScanner.NextToken();
  Account basis;
  Turn30(basis.UserID, token);
  long long p, pos;
  accountdata.Find(basis, p, pos);
  if (accountdata.excute) {
    std::cout << "Invalid\n";
    return;
  }
  if (!tokenScanner.hasMoreToken()) {
    std::cout << "Invalid\n";
    return;
  }
  token = tokenScanner.NextToken();
  Turn30(basis.Password, token);
  if (!tokenScanner.hasMoreToken()) {
    std::cout << "Invalid\n";
    return;
  }
  token = tokenScanner.NextToken();
  long long priv = token[0] - '0';
  if (priv != 0 && priv != 1 && priv != 3 && priv != 7) {
    std::cout << "Invalid\n";
    return;
  }
  if (LoginStack.back().pri <= priv) {
    std::cout << "Invalid\n";
    return;
  }
  basis.privilege = priv;
  if (!tokenScanner.hasMoreToken()) {
    std::cout << "Invalid\n";
    return;
  }
  token = tokenScanner.NextToken();
  Turn30(basis.Username, token);
  accountdata.ADD(basis);
}

inline void accountsystem::Delete(const string &input) {
  TokenScanner tokenScanner;
  tokenScanner.SetInput(input);
  if (!tokenScanner.hasMoreToken()) {
    std::cout << "Invalid\n";
    return;
  }
  string token = tokenScanner.NextToken();
  Account basis;
  Turn30(basis.UserID, token);
  long long p, pos;
  accountdata.Find(basis, p, pos);
  if (!accountdata.excute) {
    std::cout << "Invalid\n";
    return;
  }
  char check[30];
  for (long long i = 0; i < LoginStack.size(); i++) {
    Turn30(check, LoginStack[i].ID);
    if (!std::memcmp(check, basis.UserID, 30)) {
      std::cout << "Invalid\n";
      return;
    }
  }
  accountdata.DELETE(basis);
}

inline void accountsystem::SelectBook(const string &input) {
  LoginStack.back().ifSelect = true;
  LoginStack.back().Select = input;
}

inline long long accountsystem::GetPriv() const {
  if (!LOG) {
    return 0;
  }
  return LoginStack.back().pri;
}

inline bool accountsystem::IFSELECT() const {
  if (!LOG) {
    return false;
  }
  return LoginStack.back().ifSelect;
}

inline string accountsystem::GETSELECT() const {
  return LoginStack.back().Select;
}