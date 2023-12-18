#ifndef _ACCOUNTSYSTEM_HPP
#define _ACCOUNTSYSTEM_HPP
#include "database.hpp"
#include "Tool.hpp"
#include <string>
#include <vector>
struct Account{
    char UserID[30]={};
    char Password[30]={};
    char Username[30]={};
    long long privilege=0;
    bool operator<(const Account& rhs)const;
    bool operator>(const Account& rhs)const;
    bool operator==(const Account &)const{return false;};
    void print()const{for(int i=0;i<30;i++){std::cout<<UserID[i];}return;}
};
struct login{
    string ID;
    long long pri=0;
    bool ifSelect=false;
    string Select;
};
class accountsystem{
    public:
    accountsystem(const string& keyname=ACCOUNTKEY,const string& valuename=ACCOUNTVAL);
    void Su(const string& input);
    void Logout();
    void Register(const string& input);
    void Passwd(const string& input);
    void useradd(const string& input);
    void Delete(const string& input);
    void SelectBook(const string& input);
    long long GetPriv()const;
    bool IFSELECT()const;
    string GETSELECT()const;
    private:
    bool LOG=false;
    std::vector<login> LoginStack;
    database<Account> accountdata;
};
#endif