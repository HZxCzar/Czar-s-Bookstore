#ifndef _BOOKSYSTEM_HPP
#define _BOOKSYSTEM_HPP
#include "Logsystem.hpp"
#include "Tool.hpp"
#include "database.hpp"
#include <cstddef>
#include <string>
#include <type_traits>
//基础数据结构
struct Book {
  // Book() = default;
  char ISBN[20] = {};
  char BookName[60] = {};
  char Author[60] = {};
  char Keyword[60] = {};
  size_t Quantity = 0;
  double Price = 0.00;
  double TotalCost = 0.00;
  // void print()const;
};
//派生类数据结构
struct Book_ISBN : Book {
  Book_ISBN() = default;
  Book_ISBN(Book &init);
  bool operator<(const Book &) const;
  bool operator>(const Book &) const;
  bool operator==(const Book &)const{return false;};
  void print() const;
};
struct Book_NAME : Book {
  Book_NAME() = default;
  Book_NAME(Book &init);
  bool operator<(const Book &) const;
  bool operator>(const Book &) const;
  bool operator==(const Book &) const;
  void print() const;
  // void print()const;
};
struct Book_AUTHOR : Book {
  Book_AUTHOR() = default;
  Book_AUTHOR(Book &init);
  bool operator<(const Book &) const;
  bool operator>(const Book &) const;
  bool operator==(const Book &) const;
  void print() const;
  // void print()const;
};
struct Book_KEYWORD : Book {
  Book_KEYWORD() = default;
  Book_KEYWORD(Book &init);
  bool operator<(const Book &) const;
  bool operator>(const Book &) const;
  bool operator==(const Book &) const;
  void givemessage(string &elem);
  void print() const;
  // void print()const;
};
class BookSystem {
  friend class Logsystem;
  friend class database<Book_ISBN>;

public:
  BookSystem(const string &keyname1 = ISBNKEY,
             const string &valuename1 = ISBNVAL,
             const string &keyname2 = NAMEKEY,
             const string &valuename2 = NAMEVAL,
             const string &keyname3 = AUTHORKEY,
             const string &valuename3 = AUTHORVAL,
             const string &keyname4 = KEYWORDKEY,
             const string &valuename4 = KEYWORDVAL);
  void show(const string &);
  void Buy(const string &);
  void Select(const string &);
  void Modify(string &_ISBN, const string &input, string &s);
  void Import(const string &_ISBN, const string &input);
  // void CLOSE(){ISBNdata.CL();NAMEdata.CL();AUTHORdata.CL();KEYWORDdata.CL();}
private:
  database<Book_ISBN> ISBNdata;
  database<Book_NAME> NAMEdata;
  database<Book_AUTHOR> AUTHORdata;
  database<Book_KEYWORD> KEYWORDdata;
};
#endif