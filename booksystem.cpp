#include "booksystem.hpp"
#include "Logsystem.hpp"
#include "Tool.hpp"
#include "database.hpp"
#include <cassert>
#include <cstddef>
#include <cstring>
#include <iomanip>
#include <set>
#include <string>
inline BookSystem::BookSystem(const string &keyname1, const string &valuename1,
                              const string &keyname2, const string &valuename2,
                              const string &keyname3, const string &valuename3,
                              const string &keyname4,
                              const string &valuename4) {
  ISBNdata.Set(keyname1, valuename1);
  NAMEdata.Set(keyname2, valuename2);
  AUTHORdata.Set(keyname3, valuename3);
  KEYWORDdata.Set(keyname4, valuename4);
}

// inline void Book::print() const {
//   //exit(0);
//   for (long long i = 0; i < 20; i++) {
//     if (ISBN[i] == '\0') {
//       break;
//     }
//     std::cout << ISBN[i];
//   }
//   std::cout << '\t';
//   for (long long i = 0; i < 60; i++) {
//     if (BookName[i] == '\0') {
//       break;
//     }
//     std::cout << BookName[i];
//   }
//   std::cout << '\t';
//   for (long long i = 0; i < 60; i++) {
//     if (Author[i] == '\0') {
//       break;
//     }
//     std::cout << Author[i];
//   }
//   std::cout << '\t';
//   for (long long i = 0; i < 60; i++) {
//     if (Keyword[i] == '\0') {
//       break;
//     }
//     std::cout << Keyword[i];
//   }
//   std::cout << '\t';
//   std::cout << std::fixed << std::setprecision(2) << Price;
//   std::cout << '\t' << Quantity << '\n';
// }

inline void Book_ISBN::print() const {
  // exit(0);
  for (long long i = 0; i < 20; i++) {
    if (ISBN[i] == '\0') {
      break;
    }
    std::cout << ISBN[i];
  }
  std::cout << '\t';
  for (long long i = 0; i < 60; i++) {
    if (BookName[i] == '\0') {
      break;
    }
    std::cout << BookName[i];
  }
  std::cout << '\t';
  for (long long i = 0; i < 60; i++) {
    if (Author[i] == '\0') {
      break;
    }
    std::cout << Author[i];
  }
  std::cout << '\t';
  for (long long i = 0; i < 60; i++) {
    if (Keyword[i] == '\0') {
      break;
    }
    std::cout << Keyword[i];
  }
  std::cout << '\t';
  std::cout << std::fixed << std::setprecision(2) << Price;
  std::cout << '\t' << Quantity << '\n';
}

inline void Book_NAME::print() const {
  // exit(0);
  for (long long i = 0; i < 20; i++) {
    if (ISBN[i] == '\0') {
      break;
    }
    std::cout << ISBN[i];
  }
  std::cout << '\t';
  for (long long i = 0; i < 60; i++) {
    if (BookName[i] == '\0') {
      break;
    }
    std::cout << BookName[i];
  }
  std::cout << '\t';
  for (long long i = 0; i < 60; i++) {
    if (Author[i] == '\0') {
      break;
    }
    std::cout << Author[i];
  }
  std::cout << '\t';
  for (long long i = 0; i < 60; i++) {
    if (Keyword[i] == '\0') {
      break;
    }
    std::cout << Keyword[i];
  }
  std::cout << '\t';
  std::cout << std::fixed << std::setprecision(2) << Price;
  std::cout << '\t' << Quantity << '\n';
}

inline void Book_AUTHOR::print() const {
  // exit(0);
  for (long long i = 0; i < 20; i++) {
    if (ISBN[i] == '\0') {
      break;
    }
    std::cout << ISBN[i];
  }
  std::cout << '\t';
  for (long long i = 0; i < 60; i++) {
    if (BookName[i] == '\0') {
      break;
    }
    std::cout << BookName[i];
  }
  std::cout << '\t';
  for (long long i = 0; i < 60; i++) {
    if (Author[i] == '\0') {
      break;
    }
    std::cout << Author[i];
  }
  std::cout << '\t';
  for (long long i = 0; i < 60; i++) {
    if (Keyword[i] == '\0') {
      break;
    }
    std::cout << Keyword[i];
  }
  std::cout << '\t';
  std::cout << std::fixed << std::setprecision(2) << Price;
  std::cout << '\t' << Quantity << '\n';
}

inline bool Book_ISBN::operator<(const Book &rhs) const {
  for (long long i = 0; i < 20; i++) {
    if (ISBN[i] < rhs.ISBN[i]) {
      return true;
    } else if (ISBN[i] > rhs.ISBN[i]) {
      return false;
    }
  }
  return false;
}

inline void Book_KEYWORD::print() const {
  // exit(0);
  for (long long i = 0; i < 20; i++) {
    if (ISBN[i] == '\0') {
      break;
    }
    std::cout << ISBN[i];
  }
  std::cout << '\t';
  for (long long i = 0; i < 60; i++) {
    if (BookName[i] == '\0') {
      break;
    }
    std::cout << BookName[i];
  }
  std::cout << '\t';
  for (long long i = 0; i < 60; i++) {
    if (Author[i] == '\0') {
      break;
    }
    std::cout << Author[i];
  }
  std::cout << '\t';
  for (long long i = 0; i < 60; i++) {
    if (Keyword[i] == '\0') {
      break;
    }
    std::cout << Keyword[i];
  }
  std::cout << '\t';
  std::cout << std::fixed << std::setprecision(2) << Price;
  std::cout << '\t' << Quantity << '\n';
}

inline bool Book_ISBN::operator>(const Book &rhs) const {
  for (long long i = 0; i < 20; i++) {
    if (ISBN[i] > rhs.ISBN[i]) {
      return true;
    } else if (ISBN[i] < rhs.ISBN[i]) {
      return false;
    }
  }
  return false;
}

inline bool Book_NAME::operator<(const Book &rhs) const {
  for (long long i = 0; i < 60; i++) {
    if (BookName[i] < rhs.BookName[i]) {
      return true;
    } else if (BookName[i] > rhs.BookName[i]) {
      return false;
    }
  }
  if (rhs.ISBN[0] == '\0' || rhs.ISBN[0] == ' ') {
    return false;
  }
  for (long long i = 0; i < 20; i++) {
    if (ISBN[i] < rhs.ISBN[i]) {
      return true;
    } else if (ISBN[i] > rhs.ISBN[i]) {
      return false;
    }
  }
  return false;
}

inline bool Book_NAME::operator>(const Book &rhs) const {
  for (long long i = 0; i < 60; i++) {
    if (BookName[i] > rhs.BookName[i]) {
      return true;
    } else if (BookName[i] < rhs.BookName[i]) {
      return false;
    }
  }
  if (rhs.ISBN[0] == '\0' || rhs.ISBN[0] == ' ') {
    return false;
  }
  for (long long i = 0; i < 20; i++) {
    if (ISBN[i] > rhs.ISBN[i]) {
      return true;
    } else if (ISBN[i] < rhs.ISBN[i]) {
      return false;
    }
  }
  return false;
}

inline bool Book_NAME::operator==(const Book &rhs) const {
  for (long long i = 0; i < 60; i++) {
    if (BookName[i] != rhs.BookName[i]) {
      return false;
    }
  }
  return true;
}

inline bool Book_AUTHOR::operator<(const Book &rhs) const {
  for (long long i = 0; i < 60; i++) {
    if (Author[i] < rhs.Author[i]) {
      return true;
    } else if (Author[i] > rhs.Author[i]) {
      return false;
    }
  }
  if (rhs.ISBN[0] == '\0' || rhs.ISBN[0] == ' ') {
    return false;
  }
  for (long long i = 0; i < 20; i++) {
    if (ISBN[i] < rhs.ISBN[i]) {
      return true;
    } else if (ISBN[i] > rhs.ISBN[i]) {
      return false;
    }
  }
  return false;
}

inline bool Book_AUTHOR::operator>(const Book &rhs) const {
  for (long long i = 0; i < 60; i++) {
    if (Author[i] > rhs.Author[i]) {
      return true;
    } else if (Author[i] < rhs.Author[i]) {
      return false;
    }
  }
  if (rhs.ISBN[0] == '\0' || rhs.ISBN[0] == ' ') {
    return false;
  }
  for (long long i = 0; i < 20; i++) {
    if (ISBN[i] > rhs.ISBN[i]) {
      return true;
    } else if (ISBN[i] < rhs.ISBN[i]) {
      return false;
    }
  }
  return false;
}

inline bool Book_AUTHOR::operator==(const Book &rhs) const {
  for (long long i = 0; i < 60; i++) {
    if (Author[i] != rhs.Author[i]) {
      return false;
    }
  }
  return true;
}

inline bool Book_KEYWORD::operator<(const Book &rhs) const {
  for (long long i = 0; i < 60; i++) {
    if (Keyword[i] > rhs.Keyword[i]) {
      return true;
    } else if (Keyword[i] < rhs.Keyword[i]) {
      return false;
    }
  }
  if (rhs.ISBN[0] == '\0' || rhs.ISBN[0] == ' ') {
    return false;
  }
  for (long long i = 0; i < 20; i++) {
    if (ISBN[i] > rhs.ISBN[i]) {
      return true;
    } else if (ISBN[i] < rhs.ISBN[i]) {
      return false;
    }
  }
  return false;
}

inline bool Book_KEYWORD::operator>(const Book &rhs) const {
  for (long long i = 0; i < 60; i++) {
    if (Keyword[i] < rhs.Keyword[i]) {
      return true;
    } else if (Keyword[i] > rhs.Keyword[i]) {
      return false;
    }
  }
  if (rhs.ISBN[0] == '\0' || rhs.ISBN[0] == ' ') {
    return false;
  }
  for (long long i = 0; i < 20; i++) {
    if (ISBN[i] < rhs.ISBN[i]) {
      return true;
    } else if (ISBN[i] > rhs.ISBN[i]) {
      return false;
    }
  }
  return false;
}

inline bool Book_KEYWORD::operator==(const Book &rhs) const {
  for (long long i = 0; i < 60; i++) {
    if (Keyword[i] != rhs.Keyword[i]) {
      return false;
    }
  }
  return true;
}

inline void Book_KEYWORD::givemessage(string &elem) {
  elem.clear();
  for (long long i = 0; i < 20; i++) {
    elem += ISBN[i];
  }
}

inline Book_ISBN::Book_ISBN(Book &init) {
  std::memcpy(ISBN, init.ISBN, sizeof(ISBN));
  std::memcpy(BookName, init.BookName, sizeof(BookName));
  std::memcpy(Author, init.Author, sizeof(Author));
  std::memcpy(Keyword, init.Keyword, sizeof(Keyword));
  Quantity = init.Quantity;
  Price = init.Price;
  TotalCost = init.TotalCost;
}

inline Book_NAME::Book_NAME(Book &init) {
  std::memcpy(ISBN, init.ISBN, sizeof(ISBN));
  std::memcpy(BookName, init.BookName, sizeof(BookName));
  std::memcpy(Author, init.Author, sizeof(Author));
  std::memcpy(Keyword, init.Keyword, sizeof(Keyword));
  Quantity = init.Quantity;
  Price = init.Price;
  TotalCost = init.TotalCost;
}

inline Book_AUTHOR::Book_AUTHOR(Book &init) {
  std::memcpy(ISBN, init.ISBN, sizeof(ISBN));
  std::memcpy(BookName, init.BookName, sizeof(BookName));
  std::memcpy(Author, init.Author, sizeof(Author));
  std::memcpy(Keyword, init.Keyword, sizeof(Keyword));
  Quantity = init.Quantity;
  Price = init.Price;
  TotalCost = init.TotalCost;
}

inline Book_KEYWORD::Book_KEYWORD(Book &init) {
  std::memcpy(ISBN, init.ISBN, sizeof(ISBN));
  std::memcpy(BookName, init.BookName, sizeof(BookName));
  std::memcpy(Author, init.Author, sizeof(Author));
  std::memcpy(Keyword, init.Keyword, sizeof(Keyword));
  Quantity = init.Quantity;
  Price = init.Price;
  TotalCost = init.TotalCost;
}

inline void BookSystem::show(const string &input) {
  TokenScanner tokenscanner;
  TokenScanner tmpck;
  tokenscanner.SetInput(input);
  // Book_ISBN ch=ISBNdata.Get(8,0);
  // ch.print();
  // exit(0);
  //  A<Book_ISBN> ts;
  //   B<Book_ISBN> tes;
  //   ISBNdata.Afile.readA(ts,8);
  //   ISBNdata.Bfile.readA(tes,ts.pos);
  //   std::cout<<tes.size;
  //   tes.elem[0].print();exit(0);
  // exit(0);
  //  tes.elem[0].print();
  if (!tokenscanner.hasMoreToken()) {
    // std::cout<<"HERE";
    ISBNdata.PRINT();
    // std::cout << '\n';
  } else {
    string token;
    token = tokenscanner.NextTokenNIC();
    // std::cout<<token<<'\n';
    if (token == "-ISBN") {
      if (!tokenscanner.hasMoreToken()) {
        std::cout << "Invalid\n";
        return;
      }
      token = tokenscanner.BehindToken();
      if (token[0] != '=') {
        std::cout << "Invalid\n";
        return;
      }
      tokenscanner.AD();
      token = tokenscanner.NextFollow();
      tmpck.SetInput(token);
      if (!tmpck.ISISBN()) {
        std::cout << "Invalid\n";
        return;
      }
      Book_ISBN ins;
      Turn20(ins.ISBN, token);
      long long p, lastp;
      ISBNdata.FindOnly(ins, p, lastp);
      if (!ISBNdata.if_find) {
        std::cout << '\n';
      } else {
        long long pos = ISBNdata.GetInPos(ins, p);
        if (ISBNdata.excute) {
          ISBNdata.PRINT(p, p, pos, pos + 1);
        } else {
          std::cout << '\n';
        }
      }
    } else if (token == "-name") {

      if (!tokenscanner.hasMoreToken()) {
        std::cout << token << "Invalid\n";
        return;
      }
      token = tokenscanner.BehindToken();
      if (token[0] != '=') {
        std::cout << "Invalid\n";
        return;
      }
      if (token[1] != '"') {
        std::cout << "Invalid\n";
        return;
      }
      tokenscanner.AD();
      tokenscanner.AD();
      token = tokenscanner.NextFollow();
      if (token[token.size() - 1] != '"') {
        std::cout << "Invalid\n";
        return;
      }
      token.pop_back();
      tmpck.SetInput(token);
      if (!tmpck.ISNAME()) {
        std::cout << "Invalid\n";
        return;
      }
      Book_NAME ins;
      Turn60(ins.BookName, token);
      long long beg, end;
      NAMEdata.FindRange(ins, beg, end);
      if (!NAMEdata.if_find) {
        std::cout << "Invalid\n";
      } else {
        // std::cout<<"IN\n"<<beg<<" "<<end<<'\n';
        long long ind = beg;
        bool out = false;
        while (ind != end) {
          long long start = NAMEdata.GetBound(ins, ind);
          long long tail = NAMEdata.GetUp(ins, ind);
          // std::cout<<"start:"<<start<<" tail:"<<tail<<'\n';
          if (NAMEdata.if_find) {
            out = true;
            NAMEdata.PRINT(ind, ind, start, tail + 1);
          }
          ind = NAMEdata.GO(ind);
        }
        if (!out) {
          std::cout << '\n';
        }
      }
    } else if (token == "-author") {

      if (!tokenscanner.hasMoreToken()) {
        std::cout << "Invalid\n";
        return;
      }
      token = tokenscanner.BehindToken();
      if (token[0] != '=') {
        std::cout << "Invalid\n";
        return;
      }
      if (token[1] != '"') {
        std::cout << "Invalid\n";
        return;
      }
      tokenscanner.AD();
      tokenscanner.AD();
      token = tokenscanner.NextFollow();
      if (token[token.size() - 1] != '"') {
        std::cout << "Invalid\n";
        return;
      }
      token.pop_back();
      tmpck.SetInput(token);
      if (!tmpck.ISNAME()) {
        std::cout << "Invalid\n";
        return;
      }
      Book_AUTHOR ins;
      Turn60(ins.Author, token);
      long long beg, end;
      AUTHORdata.FindRange(ins, beg, end);
      if (!AUTHORdata.if_find) {
        std::cout << '\n';
      } else {
        // std::cout<<"IN\n"<<beg<<" "<<end<<'\n';
        long long ind = beg;
        bool out = false;
        while (ind != end) {
          long long start = AUTHORdata.GetBound(ins, ind);
          long long tail = AUTHORdata.GetUp(ins, ind);
          // std::cout<<"start:"<<start<<" tail:"<<tail<<'\n';
          if (AUTHORdata.if_find) {
            out = true;
            AUTHORdata.PRINT(ind, ind, start, tail + 1);
          }
          ind = AUTHORdata.GO(ind);
        }
        if (!out) {
          std::cout << '\n';
        }
      }
    } else if (token == "-keyword") {
      if (!tokenscanner.hasMoreToken()) {
        std::cout << "Invalid\n";
        return;
      }
      token = tokenscanner.BehindToken();
      if (token[0] != '=') {
        std::cout << "Invalid\n";
        return;
      }
      if (token[1] != '"') {
        std::cout << "Invalid\n";
        return;
      }
      tokenscanner.AD();
      tokenscanner.AD();
      token = tokenscanner.NextFollow();
      if (token[token.size() - 1] != '"') {
        std::cout << "Invalid\n";
        return;
      }
      token.pop_back();
      tmpck.SetInput(token);
      if (!tmpck.ISONEKEYWORD()) {
        std::cout << "Invalid\n";
        return;
      }
      Book_KEYWORD ins;
      Turn60(ins.Keyword, token);
      long long beg, end;
      KEYWORDdata.FindRange(ins, beg, end);
      if (!KEYWORDdata.if_find) {
        std::cout << '\n';
      } else {
        std::set<string> u;
        long long ind = beg;
        bool out = false;
        while (ind != end) {
          long long start = KEYWORDdata.GetBound(ins, ind);
          long long tail = KEYWORDdata.GetUp(ins, ind);
          if (KEYWORDdata.if_find) {
            out = true;
            KEYWORDdata.PUT(ind, start, tail + 1, u);
          }
          ind = KEYWORDdata.GO(ind);
        }
        if (!out) {
          std::cout << '\n';
        } else {
          auto it = u.begin();
          while (it != u.end()) {
            long long p, lastp;
            Book_ISBN ins;
            Turn20(ins.ISBN, *it);
            it++;
            long long pos;
            ISBNdata.Find(ins, p, pos);
            ISBNdata.PRINT(p, p, pos, pos + 1);
          }
        }
      }
    } else {
      std::cout << "Invalid\n";
      return;
    }
  }
}

inline void BookSystem::Buy(const string &input) {
  TokenScanner tokenscanner;
  TokenScanner tmpck;
  tokenscanner.SetInput(input);
  string token;
  if (!tokenscanner.hasMoreToken()) {
    std::cout << "Invalid\n";
    return;
  }
  token = tokenscanner.NextToken();
  tmpck.SetInput(token);
  if (!tmpck.ISISBN()) {
    std::cout << "Invalid\n";
    return;
  }
  Book_ISBN ins;
  Turn20(ins.ISBN, token);
  if (!tokenscanner.hasMoreToken()) {
    std::cout << "Invalid\n";
    return;
  }
  token = tokenscanner.NextToken();
  tmpck.SetInput(token);
  if (!tmpck.ISQUANTITY()) {
    std::cout << "Invalid\n";
    return;
  }
  if (token[0] == '-') {
    std::cout << "Invalid\n";
    return;
  }
  if (!tokenscanner.ISDIGIT(token)) {
    std::cout << "Invalid\n";
    return;
  }
  size_t Quant = tokenscanner.StringToSizeT(token);
  long long p, pos;
  ISBNdata.Find(ins, p, pos);
  if (ISBNdata.excute == false) {
    std::cout << "Invalid\n";
    return;
  }
  Book_ISBN tag = ISBNdata.Get(p, pos);
  long double pay = tag.Price * Quant * 1.00;
  if (Quant > 2147483647) {
    std::cout << "Invalid\n";
    return;
  }
  if (tag.Quantity < Quant || Quant <= 0) {
    std::cout << "Invalid\n";
    return;
  }
  tag.Quantity -= Quant;
  std::cout << std::fixed << std::setprecision(2) << pay << '\n';
  ISBNdata.Update(tag, p, pos);
  Book basis;
  std::memcpy(basis.ISBN, tag.ISBN, sizeof(tag.ISBN));
  std::memcpy(basis.BookName, tag.BookName, sizeof(tag.BookName));
  std::memcpy(basis.Author, tag.Author, sizeof(tag.Author));
  std::memcpy(basis.Keyword, tag.Keyword, sizeof(tag.Keyword));
  basis.Quantity = tag.Quantity;
  basis.Price = tag.Price;
  basis.TotalCost = tag.TotalCost;
  //修改的quantity不会影响查找，可以直接找
  Book_NAME insN(basis);
  NAMEdata.Find(insN, p, pos);
  NAMEdata.Update(insN, p, pos);

  Book_AUTHOR insA(basis);
  AUTHORdata.Find(insA, p, pos);
  AUTHORdata.Update(insA, p, pos);

  // Book_KEYWORD insK(basis);
  // KEYWORDdata.Find(insK, p, pos);
  // KEYWORDdata.Update(insK, p, pos);
  //修改日志
  Logsystem LOGSYSTEM;
  LOGSYSTEM.IN(pay);
}

inline void BookSystem::Select(const string &input) {
  Book basis;
  Turn20(basis.ISBN, input);
  Book_ISBN insI(basis);
  long long p, pos;
  // insI.PRINT();
  ISBNdata.Find(insI, p, pos);
  if (!ISBNdata.excute) {
    // std::cout<<"ADD NEW\n";
    ISBNdata.ADD(insI);

    Book_NAME insN(basis);
    NAMEdata.ADD(insN);

    Book_AUTHOR insA(basis);
    AUTHORdata.ADD(insA);

    Book_KEYWORD insK(basis);
    KEYWORDdata.ADD(insK);
  }
}

inline void BookSystem::Modify(string &_ISBN, const string &input, string &s) {
  s.clear();
  if (_ISBN.empty()) {
    std::cout << "Invalid\n";
    return;
  }
  Book basis;
  Book after;
  // std::cout<<_ISBN<<'\n';
  Turn20(basis.ISBN, _ISBN);
  // std::cout<<"check:"<<basis.ISBN[0]<<basis.ISBN[1];
  Book_ISBN stream(basis);
  long long p, pos;
  ISBNdata.Find(stream, p, pos);
  Book_ISBN tag = ISBNdata.Get(p, pos);
  std::memcpy(basis.ISBN, tag.ISBN, sizeof(tag.ISBN));
  std::memcpy(basis.BookName, tag.BookName, sizeof(tag.BookName));
  std::memcpy(basis.Author, tag.Author, sizeof(tag.Author));
  std::memcpy(basis.Keyword, tag.Keyword, sizeof(tag.Keyword));

  std::memcpy(after.ISBN, tag.ISBN, sizeof(tag.ISBN));
  std::memcpy(after.BookName, tag.BookName, sizeof(tag.BookName));
  std::memcpy(after.Author, tag.Author, sizeof(tag.Author));
  std::memcpy(after.Keyword, tag.Keyword, sizeof(tag.Keyword));
  after.Quantity = tag.Quantity;
  after.Price = tag.Price;
  after.TotalCost = tag.TotalCost;
  TokenScanner tokenscanner;
  TokenScanner tmpck;
  tokenscanner.SetInput(input);
  string token;
  bool IS = false, NA = false, AU = false, KW = false, PR = false;
  while (tokenscanner.hasMoreToken()) {
    token = tokenscanner.NextTokenNIC();
    // std::cout<<"check:"<<basis.ISBN[0]<<basis.ISBN[1];
    // std::cout<<"token:"<<token<<'\n';
    if (!tokenscanner.hasMoreToken()) {
      std::cout << "Invalid\n";
      return;
    } else if (token == "-ISBN") {
      // std::cout<<"IN!\n";
      if (IS) {
        std::cout << "Invalid\n";
        return;
      }
      IS = true;
      token = tokenscanner.BehindToken();
      if (token[0] != '=') {
        std::cout << "Invalid\n";
        return;
      }
      tokenscanner.AD();
      token = tokenscanner.NextFollow();
      tmpck.SetInput(token);
      if (!tmpck.ISISBN()) {
        std::cout << "Invalid\n";
        return;
      }
      char check[20] = {};
      Turn20(check, token);
      Book_ISBN ins;
      Turn20(ins.ISBN, token);
      long long ckp, ckpos;
      ISBNdata.Find(ins, p, pos);
      if (ISBNdata.excute) {
        std::cout << "Invalid\n";
        return;
      }
      if (memcmp(after.ISBN, check, 20)) {
        Turn20(after.ISBN, token);
        // std::cout<<"check:"<<basis.ISBN[0]<<basis.ISBN[1];
      } else {
        std::cout << "Invalid\n";
        return;
      }
    } else if (token == "-name") {
      if (NA) {
        std::cout << "Invalid\n";
        return;
      }
      NA = true;
      token = tokenscanner.BehindToken();
      if (token[0] != '=') {
        std::cout << "Invalid\n";
        return;
      }
      if (token[1] != '"') {
        std::cout << "Invalid\n";
        return;
      }
      tokenscanner.AD();
      tokenscanner.AD();
      token = tokenscanner.NextFollow();
      if (token[token.size() - 1] != '"') {
        std::cout << "Invalid\n";
        return;
      }
      token.pop_back();
      tmpck.SetInput(token);
      if (!tmpck.ISNAME()) {
        std::cout << "Invalid\n";
        return;
      }
      Turn60(after.BookName, token);
    } else if (token == "-author") {
      if (AU) {
        std::cout << "Invalid\n";
        return;
      }
      AU = true;
      token = tokenscanner.BehindToken();
      if (token[0] != '=') {
        std::cout << "Invalid\n";
        return;
      }
      if (token[1] != '"') {
        std::cout << "Invalid\n";
        return;
      }
      tokenscanner.AD();
      tokenscanner.AD();
      token = tokenscanner.NextFollow();
      if (token[token.size() - 1] != '"') {
        std::cout << "Invalid\n";
        return;
      }
      token.pop_back();
      tmpck.SetInput(token);
      if (!tmpck.ISNAME()) {
        std::cout << "Invalid\n";
        return;
      }
      Turn60(after.Author, token);
    } else if (token == "-keyword") {
      if (KW) {
        std::cout << "Invalid\n";
        return;
      }
      KW = true;
      token = tokenscanner.BehindToken();
      if (token[0] != '=') {
        std::cout << "Invalid\n";
        return;
      }
      if (token[1] != '"') {
        std::cout << "Invalid\n";
        return;
      }
      tokenscanner.AD();
      tokenscanner.AD();
      token = tokenscanner.NextFollow();
      if (token[token.size() - 1] != '"') {
        std::cout << "Invalid\n";
        return;
      }
      token.pop_back();
      if (token[0] == '|' || token[token.size() - 1] == '|') {
        std::cout << "Invalid\n";
        return;
      }
      tmpck.SetInput(token);
      if (!tmpck.ISKEYWORD()) {
        std::cout << "Invalid\n";
        return;
      }
      TokenScanner checktk;
      checktk.SetInput(token);
      std::set<string> test;
      string ck;
      while (checktk.hasMoreToken()) {
        ck = checktk.NextKeyword();
        if (test.count(ck)) {
          std::cout << "Invalid\n";
          return;
        }
        test.insert(ck);
      }
      Turn60(after.Keyword, token);
    } else if (token == "-price") {
      if (PR) {
        std::cout << "Invalid\n";
        return;
      }
      PR = true;
      token = tokenscanner.BehindToken();
      if (token[0] != '=') {
        std::cout << "Invalid\n";
        return;
      }
      tokenscanner.AD();
      token = tokenscanner.NextFollow();
      tmpck.SetInput(token);
      if (!tmpck.ISPRICE()) {
        std::cout << "Invalid\n";
        return;
      }
      long double p = tokenscanner.StringToDouble(token) * 1.00;
      after.Price = p;
    } else {
      std::cout << "Invalid\n";
      return;
    }
  }
  for (int i = 0; i < 20; i++) {
    if (after.ISBN[i] == '\0') {
      break;
    }
    s += after.ISBN[i];
  }
  // std::cout<<"1\n";
  Book_ISBN insI(basis); // insI.print();
  Book_ISBN aftI(after);
  ISBNdata.DELETE(insI);
  // std::cout<<"AFT:";
  // aftI.print();
  ISBNdata.ADD(aftI);

  Book_NAME insN(basis);
  Book_NAME aftN(after);
  NAMEdata.DELETE(insN);
  NAMEdata.ADD(aftN);

  Book_AUTHOR insA(basis);
  Book_AUTHOR aftA(after);
  AUTHORdata.DELETE(insA);
  AUTHORdata.ADD(aftA);

  if (KW) {
    TokenScanner tokenScanner;
    string baseline, tok, afterline;
    for (long long i = 0; i < 60; i++) {
      baseline = baseline + basis.Keyword[i];
    }
    tokenScanner.SetInput(baseline);
    Book_KEYWORD insK(basis);
    Book_KEYWORD aftK(after);
    while (tokenScanner.hasMoreToken()) {
      tok = tokenScanner.NextKeyword();
      Turn60(insK.Keyword, tok);
      KEYWORDdata.DELETE(insK);
      // insK.PRINT();
    }
    // std::cout<<"-----------------------------\n";
    for (long long i = 0; i < 60; i++) {
      afterline = afterline + after.Keyword[i];
    }
    tokenScanner.SetInput(afterline);
    while (tokenScanner.hasMoreToken()) {
      tok = tokenScanner.NextKeyword();
      Turn60(aftK.Keyword, tok);
      KEYWORDdata.ADD(aftK);
      // aftK.PRINT();
    }
  }
}

inline void BookSystem::Import(const string &_ISBN, const string &input) {
  if (_ISBN.empty()) {
    std::cout << "Invalid\n";
    return;
  }
  TokenScanner tmpck;
  Book basis;
  Turn20(basis.ISBN, _ISBN);
  Book_ISBN stream(basis);
  long long p, pos;
  ISBNdata.Find(stream, p, pos);
  Book_ISBN tag = ISBNdata.Get(p, pos);
  std::memcpy(basis.ISBN, tag.ISBN, sizeof(tag.ISBN));
  std::memcpy(basis.BookName, tag.BookName, sizeof(tag.BookName));
  std::memcpy(basis.Author, tag.Author, sizeof(tag.Author));
  std::memcpy(basis.Keyword, tag.Keyword, sizeof(tag.Keyword));
  basis.Quantity = tag.Quantity;
  basis.Price = tag.Price;
  basis.TotalCost = tag.TotalCost;
  TokenScanner tokenscanner;
  tokenscanner.SetInput(input);
  string token = tokenscanner.NextToken();
  tmpck.SetInput(token);
  if (!tmpck.ISQUANTITY()) {
    std::cout << "Invalid\n";
    return;
  }
  if (token[0] == '-') {
    std::cout << "Invalid\n";
    return;
  }
  if (!tokenscanner.ISDIGIT(token)) {
    std::cout << "Invalid\n";
    return;
  }
  // std::cout<<token<<'\n';
  size_t Quant = tokenscanner.StringToSizeT(token);
  if (Quant == 0) {
    std::cout << "Invalid\n";
    return;
  }
  if (Quant > 2147483647) {
    std::cout << "Invalid\n";
    return;
  }
  // std::cout<<Quant<<'\n';
  basis.Quantity += Quant;
  token = tokenscanner.NextToken();
  tmpck.SetInput(token);
  if (!tmpck.ISPRICE()) {
    std::cout << "Invalid\n";
    return;
  }
  if (token[0] == '-') {
    std::cout << "Invalid\n";
    return;
  }
  long double totcost = tokenscanner.StringToDouble(token);
  totcost *= 1.00;
  if (totcost == 0.00) {
    std::cout << "Invalid\n";
    return;
  }
  basis.TotalCost += totcost;

  Book_ISBN insI(basis);
  ISBNdata.Find(insI, p, pos);
  ISBNdata.Update(insI, p, pos);

  Book_NAME insN(basis);
  NAMEdata.Find(insN, p, pos);
  NAMEdata.Update(insN, p, pos);

  Book_AUTHOR insA(basis);
  AUTHORdata.Find(insA, p, pos);
  AUTHORdata.Update(insA, p, pos);

  // Book_KEYWORD insK(basis);
  // KEYWORDdata.Find(insK, p, pos);
  // KEYWORDdata.Update(insK, p, pos);

  //修改日志
  long double pay = totcost * 1.00;
  // std::cout<<"pay"<<pay<<'\n';
  Logsystem LOGSYSTEM;
  LOGSYSTEM.OUT(pay);
}
