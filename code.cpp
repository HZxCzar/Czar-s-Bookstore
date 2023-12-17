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
#include <cassert>

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
  string s;
  accountsystem ACCOUNTSYSTEM;
  BookSystem BOOKSYSTEM;
  Logsystem LOGSYSTEM;
  TokenScanner tokenscanner;
  string input;
  string token, check;
  string ord, ISBN;
  TokenScanner tmpck;
  while (true) {
    // std::cout<<"ENTER\n";
    input.clear();
    char t;
    while((t=getchar())!='\n'&& t!='\r'&& t!=EOF)
    {
      input+=t;
    }
    //getline(std::cin, input);
    tokenscanner.SetInput(input);
    if (!tokenscanner.hasMoreToken()) {
      if(t==EOF)
      {
        return 0;
      }
      continue;
    }
    string ord = tokenscanner.BehindToken();
    if (!tokenscanner.ALLASCILL(ord)) {
      std::cout << "Invalid\n";
      continue;
    }
    token = tokenscanner.NextToken();
    if (token == "su") {
      if (ACCOUNTSYSTEM.GetPriv() >= 0) {
        ord = tokenscanner.BehindToken();
        tokenscanner.NextToken();
        tokenscanner.NextToken();
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
        tokenscanner.NextToken();
        tokenscanner.NextToken();
        tokenscanner.NextToken();
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
        tokenscanner.NextToken();
        tokenscanner.NextToken();
        tokenscanner.NextToken();
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
        tokenscanner.NextToken();
        tokenscanner.NextToken();
        tokenscanner.NextToken();
        tokenscanner.NextToken();
        if (tokenscanner.hasMoreToken()) {
          std::cout << "?Invalid\n";
          continue;
        }
        ACCOUNTSYSTEM.useradd(ord);
      } else {
        std::cout << "Invalid\n";
      }
    } else if (token == "delete") {
      if (ACCOUNTSYSTEM.GetPriv() >= 7) {
        ord = tokenscanner.BehindToken();
        tokenscanner.NextToken();
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
      token = tokenscanner.NextTokenNIC();
      if (token == "finance") {
        ord = tokenscanner.BehindToken();
        if (ACCOUNTSYSTEM.GetPriv() >= 7) {
          tokenscanner.NextToken();
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
          if (tokenscanner.hasMoreToken()) {
            token = tokenscanner.BehindToken();
            //std::cout<<token<<'\n';
            if (token[0] != '=') {
              std::cout << "Invalid\n";
              continue;
            }
            tokenscanner.AD();
            token=tokenscanner.NextToken();
            //std::cout<<"Token:"<<token<<'\n';
            if (tokenscanner.hasMoreToken()) {
              std::cout << "Invalid\n";
              continue;
            }
          }
          //std::cout<<"OK"<<ord<<'\n';
          BOOKSYSTEM.show(ord);
        } else {
          std::cout << "Invalid\n";
        }
      }
    } else if (token == "buy") {
      if (ACCOUNTSYSTEM.GetPriv() >= 1) {
        ord = tokenscanner.BehindToken();
        tokenscanner.NextToken();
        tokenscanner.NextTokenNIC();
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
        tmpck.SetInput(ord);
        if (!tmpck.ISISBN()) {
          std::cout << "Invalid\n";
          continue;
        }
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
          //std::cout<<"HERE\n";
          BOOKSYSTEM.Modify(ISBN, ord, s);
          //std::cout<<"NEW SELECT"<<ISBN<<'\n';
          if (!s.empty()) {
            //std::cout<<"IN\n";
            //std::cout<<s<<"<<\n";
            ACCOUNTSYSTEM.SelectBook(s);
          }
        } else {
          std::cout << "Invalid\n";
        }
      } else {
        std::cout << "Invalid\n";
      }
    } else if (token == "import") {
      assert(0);
      if (ACCOUNTSYSTEM.GetPriv() >= 3) {
        if (ACCOUNTSYSTEM.IFSELECT()) {
          ord = tokenscanner.BehindToken();
          tokenscanner.NextISBN();
          tokenscanner.NextTokenNIC();
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