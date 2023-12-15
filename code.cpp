#include "Accountssystem.cpp"
#include "Accountssystem.hpp"
#include "FileWriting.hpp"
#include "Logsystem.cpp"
#include "Logsystem.hpp"
#include "Tool.cpp"
#include "Tool.hpp"
#include "booksystem.cpp"
#include "booksystem.hpp"
#include "database.cpp"
#include "database.hpp"
#include <bits/types/FILE.h>
#include <cstdio>
#include <iostream>
#include <string>

int main() {
  // std::remove(ACCOUNTKEY.c_str());
  // std::remove(ACCOUNTVAL.c_str());
  // std::remove(ISBNKEY.c_str());
  // std::remove(ISBNVAL.c_str());
  // std::remove(NAMEKEY.c_str());
  // std::remove(NAMEVAL.c_str());
  // std::remove(AUTHORKEY.c_str());
  // std::remove(AUTHORVAL.c_str());
  // std::remove(KEYWORDKEY.c_str());
  // std::remove(KEYWORDVAL.c_str());
  // std::remove(LOGKEY.c_str());
  // std::remove(LOGVAL.c_str());
  bool s = false;
  accountsystem ACCOUNTSYSTEM;
  BookSystem BOOKSYSTEM;
  Logsystem LOGSYSTEM;
  TokenScanner tokenscanner;
  string input;
  string token, check;
  string ord, ISBN;
  while (true) {
    // std::cout<<"ENTER\n";
    getline(std::cin, input);
    if (std::cin.eof()) {
      return 0;
    }
    tokenscanner.SetInput(input);
    if (!tokenscanner.hasMoreToken()) {
      continue;
    }
    string ord = tokenscanner.BehindToken();
    if (!tokenscanner.ALLASCILL(ord)) {
      std::cout << "Invalid\n";
      continue;
    }
    // Logsystem TEST;
    token = tokenscanner.NextToken();
    if (token == "su") {
      if (ACCOUNTSYSTEM.GetPriv() >= 0) {
        ord = tokenscanner.BehindToken();
        tokenscanner.NextKeyword();
        tokenscanner.NextKeyword();
        if (tokenscanner.hasMoreToken()) {
          std::cout << "Invalid\n";
          continue;
        }
        ACCOUNTSYSTEM.Su(ord);
      } else {
        std::cout << "Invalid\n";
      }
    } else if (token == "logout") {
      if (ACCOUNTSYSTEM.GetPriv() >= 1) {
        if (tokenscanner.hasMoreToken()) {
          std::cout << "Invalid\n";
          continue;
        }
        ACCOUNTSYSTEM.Logout();
      } else {
        std::cout << "Invalid\n";
      }
    } else if (token == "register") {
      if (ACCOUNTSYSTEM.GetPriv() >= 0) {
        ord = tokenscanner.BehindToken();
        tokenscanner.NextKeyword();
        tokenscanner.NextKeyword();
        tokenscanner.NextKeyword();
        if (tokenscanner.hasMoreToken()) {
          std::cout << "Invalid\n";
          continue;
        }
        ACCOUNTSYSTEM.Register(ord);
      } else {
        std::cout << "Invalid\n";
      }
    } else if (token == "passwd") {
      if (ACCOUNTSYSTEM.GetPriv() >= 1) {
        ord = tokenscanner.BehindToken();
        tokenscanner.NextKeyword();
        tokenscanner.NextKeyword();
        tokenscanner.NextKeyword();
        if (tokenscanner.hasMoreToken()) {
          std::cout << "Invalid\n";
          continue;
        }
        ACCOUNTSYSTEM.Passwd(ord);
      } else {
        std::cout << "Invalid\n";
      }
    } else if (token == "useradd") {
      if (ACCOUNTSYSTEM.GetPriv() >= 3) {
        ord = tokenscanner.BehindToken();
        tokenscanner.NextKeyword();
        tokenscanner.NextKeyword();
        tokenscanner.NextKeyword();
        tokenscanner.NextKeyword();
        if (tokenscanner.hasMoreToken()) {
          std::cout << "Invalid\n";
          continue;
        }
        ACCOUNTSYSTEM.useradd(ord);
      } else {
        std::cout << "Invalid\n";
      }
    } else if (token == "delete") {
      if (ACCOUNTSYSTEM.GetPriv() >= 7) {
        ord = tokenscanner.BehindToken();
        tokenscanner.NextKeyword();
        if (tokenscanner.hasMoreToken()) {
          std::cout << "Invalid\n";
          continue;
        }
        ACCOUNTSYSTEM.Delete(ord);
      } else {
        std::cout << "Invalid\n";
      }
    } else if (token == "show") {
      ord = tokenscanner.BehindToken();
      token = tokenscanner.NextToken();
      if (token == "finance") {
        ord = tokenscanner.BehindToken();
        if (ACCOUNTSYSTEM.GetPriv() >= 7) {
          tokenscanner.NextKeyword();
          tokenscanner.NextKeyword();
          if (tokenscanner.hasMoreToken()) {
            std::cout << "Invalid\n";
            continue;
          }
          LOGSYSTEM.ShowFinance(ord);
        } else {
          std::cout << "Invalid\n";
        }
      } else {
        if (ACCOUNTSYSTEM.GetPriv() >= 1) {
          tokenscanner.NextKeyword();
          if (tokenscanner.hasMoreToken()) {
            std::cout << "Invalid\n";
            continue;
          }
          BOOKSYSTEM.show(ord);
        } else {
          std::cout << "Invalid\n";
        }
      }
    } else if (token == "buy") {
      if (ACCOUNTSYSTEM.GetPriv() >= 1) {
        ord = tokenscanner.BehindToken();
        tokenscanner.NextISBN();
        tokenscanner.NextToken();
        if (tokenscanner.hasMoreToken()) { // hasMore如何界定“”
          std::cout << "Invalid\n";
          continue;
        }
        BOOKSYSTEM.Buy(ord);
      } else {
        std::cout << "Invalid\n";
      }
    } else if (token == "select") {
      if (ACCOUNTSYSTEM.GetPriv() >= 3) {
        ord = tokenscanner.NextISBN();
        if (tokenscanner.hasMoreToken()) {
          std::cout << "Invalid\n";
          continue;
        }
        BOOKSYSTEM.Select(ord);
        ACCOUNTSYSTEM.SelectBook(ord);
      } else {
        std::cout << "Invalid\n";
      }
    } else if (token == "modify") {
      if (ACCOUNTSYSTEM.GetPriv() >= 3) {
        if (ACCOUNTSYSTEM.IFSELECT()) {
          ord = tokenscanner.BehindToken();
          ISBN = ACCOUNTSYSTEM.GETSELECT();
          BOOKSYSTEM.Modify(ISBN, ord, s);
          // std::cout<<"NEW SELECT"<<ISBN<<'\n';
          if (s) {
            ACCOUNTSYSTEM.SelectBook(ISBN);
          }
        } else {
          std::cout << "Invalid\n";
        }
      } else {
        std::cout << "Invalid\n";
      }
    } else if (token == "import") {
      if (ACCOUNTSYSTEM.GetPriv() >= 3) {
        if (ACCOUNTSYSTEM.IFSELECT()) {
          ord = tokenscanner.BehindToken();
          tokenscanner.NextISBN();
          tokenscanner.NextToken();
          if (tokenscanner.hasMoreToken()) {
            std::cout << "Invalid\n";
            continue;
          }
          ISBN = ACCOUNTSYSTEM.GETSELECT();
          BOOKSYSTEM.Import(ISBN, ord);
        } else {
          std::cout << "Invalid\n";
        }
      } else {
        std::cout << "Invalid\n";
      }
    } else if (token == "quit" || token == "exit") {
      return 0;
    } else {
      std::cout << "Invalid\n";
    }
  }
}