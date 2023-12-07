#include <cstdarg>
#include <cstddef>
#include <fstream>
#include <iostream>
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
constexpr int BLOCKSIZE = 555;
bool check = false;
struct data {
  int value ;
  char index[64] = {};
};
struct partA {
  int blockpos = 0;
  int next = 0;
  data first;
};
struct partB {
  data elem[BLOCKSIZE + 100];
  int size = 0;
};
template <class partA, class partB> class MemoryRiver {
private:
  fstream file;
  string file_name;
  int sizeofi = sizeof(partA);
  int sizeofv = sizeof(partB);

public:
  MemoryRiver() = default;
  MemoryRiver(const string &file_name) : file_name(file_name) {}
  void Op() { file.open(file_name, std::ios::in | std::ios::out); }
  void Cl() { file.close(); }
  void Setfile(const string &name) { file_name = name; }
  void initialise() {
    file.open(file_name, std::ios::out);
    partA tmp;
    int beg = 0;
    file.write(reinterpret_cast<char *>(&beg), sizeof(int));
    for (int i = 0; i < 11451; ++i) {
      file.write(reinterpret_cast<char *>(&tmp), sizeofi);
    }
    file.close();
  }
  void Clear() {
    file.open(file_name, std::ios::out);
    file.close();
  }
  //检查是否是第一次打开
  bool IS_FIRST_OPEN() {
    file.open(file_name, std::ios::in | std::ios::out | std::ios::ate);
    if (!file.is_open()) {
      ofstream file(file_name);
      file.open(file_name, std::ios::in | std::ios::out | std::ios::ate);
      file.close();
      return true;
    }
    if (0 < file.tellp()) {
      file.close();
      return false;
    } else {
      file.close();
      return true;
    }
  }
  void get_info(int &tmp) {
    file.seekg(0);
    file.read(reinterpret_cast<char *>(&tmp), sizeof(int));
  }
  void write_info(int tmp) {
    file.close();
    file.open(file_name,std::ios::out | std::ios::in);
    file.seekp(0);
    file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
  }
  //在文件合适位置写入类对象t，并返回写入的位置索引index
  //位置索引意味着当输入正确的位置索引index，在以下三个函数中都能顺利的找到目标对象进行操作
  //位置索引index可以取为对象写入的起始位置
  int writeA(partA &t) {
    // file.close();
    // file.open(file_name, std::ios::out | std::ios::in);
    int num;
    get_info(num);
    long long pos = num * sizeofi + sizeof(int);
    file.seekp(pos);
    file.write(reinterpret_cast<char *>(&t), sizeofi);
    write_info(num + 1);
    return pos;
  }
  int writeB(partB &t) {
    file.close();
    file.open(file_name, std::ios::out | std::ios::in | std::ios::ate);
    long long pos = file.tellp();
    file.write(reinterpret_cast<char *>(&t), sizeofv);
    return pos;
  }

  //用t的值更新位置索引index对应的对象，保证调用的index都是由write函数产生
  void updateA(partA &t, const int index) {
    file.seekp(index);
    file.write(reinterpret_cast<char *>(&t), sizeofi);
  }
  void updateB(partB &t, const int index) {
    file.seekp(index);
    file.write(reinterpret_cast<char *>(&t), sizeofv);
  }

  //读出位置索引index对应的T对象的值并赋值给t，保证调用的index都是由write函数产生
  void readA(partA &t, const int index) {
    file.seekg(index);
    file.read(reinterpret_cast<char *>(&t), sizeofi);
  }
  void readB(partB &t, const int index) {
    file.seekg(index);
    file.read(reinterpret_cast<char *>(&t), sizeofv);
  }

  //删除位置索引index对应的对象(不涉及空间回收时，可忽略此函数)，保证调用的index都是由write函数产生
  void Delete(int index) { /* your code here */
  }
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool outflag = false;
class database {
public:
  database() = default;
  database(const string &name);
  //插入index数据value
  void Insert(const string &ind, const int &val);
  //删除index数据value，可能不存在
  void Delete(const string &ind, const int &val);
  //找到index（可能不存在，则输出null），并升序输出
  void Find(const std::string &ind);
  bool RUN(const int &val, const partA &block, const char (&ind)[64]);
  void BREAK(partA &A, partB &B);
  bool have_ind;
  bool have_val;
  bool checkbeg = false;
  void StreamPrint();

private:
  //二分查找value
  int BinarySearch(const int &val, const partB &block, const char (&index)[64]);
  //添加value
  void ADD(const int &val, partB &block, const char (&index)[64]);
  //删除pos
  void DELETE(const int &val, partB &block, const char (&index)[64]);
  MemoryRiver<partA, partB> datafile;
  bool empt = false;
};
//判断是否小于
inline bool MyCompareS(const char (&rhs)[64], const char (&lhs)[64]) {
  for (int i = 0; i < 64; i++) {
    if (rhs[i] == '\0' || lhs[i] == '\0') {
      if (rhs[i] == '\0' && lhs[i] == '\0') {
        return false;
      }
      if (rhs[i] == '\0') {
        return true;
      }
      if (lhs[i] == '\0') {
        return false;
      }
    } else if (rhs[i] < lhs[i]) {
      return true;
    } else if (rhs[i] > lhs[i]) {
      return false;
    }
  }
  return false;
}
//判断是否大于
inline bool MyCompareL(const char (&rhs)[64], const char (&lhs)[64]) {
  for (int i = 0; i < 64; i++) {
    if (rhs[i] == '\0' || lhs[i] == '\0') {
      if (rhs[i] == '\0' && lhs[i] == '\0') {
        return false;
      }
      if (rhs[i] == '\0') {
        return false;
      }
      if (lhs[i] == '\0') {
        return true;
      }
    } else if (rhs[i] < lhs[i]) {
      return false;
    } else if (rhs[i] > lhs[i]) {
      return true;
    }
  }
  return false;
}

inline bool MyCompareE(const char (&rhs)[64], const char (&lhs)[64]) {
  for (int i = 0; i < 64; i++) {
    if (rhs[i] != lhs[i]) {
      return false;
    }
    if (rhs[i] == '\0' && lhs[i] == '\0') {
      break;
    }
  }
  return true;
}

inline database::database(const string &name) {
  datafile.Setfile(name);
  //datafile.Clear();
  if (datafile.IS_FIRST_OPEN()) {
    empt = true;
    datafile.initialise();
  } else {
    datafile.Op();
    int tmp;
    datafile.get_info(tmp);
    if (tmp == 0) {
      datafile.write_info(0);
      empt = true;
    }
    datafile.Cl();
  }
}

inline void TurnType(const string &str, char (&elem)[64]) {
  for (int i = 0; i < str.size(); i++) {
    elem[i] = str[i];
  }
}

inline void initchar(char (&lhs)[64], const char (&ind)[64]) {
  for (int i = 0; i < 64; i++) {
    lhs[i] = ind[i];
  }
}

inline int database::BinarySearch(const int &val, const partB &block,
                                  const char (&index)[64]) {
  int left = 0, right = block.size - 1, mid, value, checkflag;
  while (left < right) {
    mid = (left + right) / 2;
    if (MyCompareL(index, block.elem[mid].index)) {
      left = mid + 1;
    } else if (MyCompareS(index, block.elem[mid].index)) {
      right = mid;
    } else {
      value = block.elem[mid].value;
      if (value < val) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
  }
  have_ind = true;
  have_val = true;
  if (!MyCompareE(index, block.elem[right].index)) {
    have_ind = false;
  } else if (block.elem[right].value < val) {
    have_val = false;
  }
  //if(right<0)right=0;
  return right;
}

inline void database::ADD(const int &val, partB &block,
                          const char (&index)[64]) {
  checkbeg = false;
  int pos = BinarySearch(val, block, index);
  //std::cout<<pos<<'\n';
  data add;
  initchar(add.index, index);
  add.value = val;
  if (!have_ind) {
    if (MyCompareL(index, block.elem[pos].index)) {
      pos++;
    }
    for (int i = block.size; i > pos; i--) {
      block.elem[i] = block.elem[i - 1];
    }
    if (pos == 0)
      checkbeg = true;
    block.elem[pos] = add;
    block.size++;
  } else {
    if (!have_val) {
      pos++;
      for (int i = block.size; i > pos; i--) {
        block.elem[i] = block.elem[i - 1];
      }
      if (pos == 0)
        checkbeg = true;
      block.elem[pos] = add;
      block.size++;
    } else {
      if (val == block.elem[pos].value) {
        return;
      }
      for (int i = block.size; i > pos; i--) {
        block.elem[i] = block.elem[i - 1];
      }
      if (pos == 0)
        checkbeg = true;
      block.elem[pos] = add;
      block.size++;
    }
  }
}

inline void database::DELETE(const int &val, partB &block,
                             const char (&index)[64]) {
  check = false;
  int pos = BinarySearch(val, block, index);
  if (!have_ind || !have_val || block.elem[pos].value != val) {
    return;
  } else {
    for (int i = pos; i < block.size; i++) {
      block.elem[i] = block.elem[i + 1];
    }
    if (pos == 0)
      checkbeg = true;
    block.size--;
    if (MyCompareE(block.elem[pos].index, index)) {
      if ((pos < 1 || !MyCompareE(block.elem[pos - 1].index, index)) &&
          (pos >= block.size - 1 ||
           !MyCompareE(block.elem[pos + 1].index, index))) {
        check = true;
      }
    }
  }
}

inline bool database::RUN(const int &val, const partA &block,
                          const char (&ind)[64]) {
  if (block.next == -1) {
    return true;
  }
  if (MyCompareS(block.first.index, ind)) {
    partA nextA;
    datafile.readA(nextA, block.next);
    if (MyCompareL(nextA.first.index, ind)) {
      return true;
    } else if (MyCompareS(nextA.first.index, ind)) {
      return false;
    } else {
      if (nextA.first.value <= val) {
        return false;
      } else {
        return true;
      }
    }
  }
  if (MyCompareE(block.first.index, ind)) {
    partA nextA;
    datafile.readA(nextA, block.next);
    if (MyCompareE(nextA.first.index, ind)) {
      if (nextA.first.value <= val) {
        return false;
      }
    }
  }
  return true;
}

inline void database::Insert(const string &ind, const int &val) {
  datafile.Op();
  char index[64] = {};
  partA A;
  partB B;
  TurnType(ind, index);
  if (empt) {
    initchar(A.first.index, index);
    A.first.value = val;
    A.next = -1;
    ADD(val, B, index);
    empt = false;
    A.blockpos = datafile.writeB(B);
    datafile.writeA(A);
    datafile.Cl();
    return;
  } else {
    int p = sizeof(int), lastp = p;
    partA stream;
    datafile.readA(stream, p);
    while (!RUN(val, stream, index)) {
      lastp = p;
      p = stream.next;
      datafile.readA(stream, p);
    }
    datafile.readB(B, stream.blockpos);
    ADD(val, B, index);
    if (checkbeg) {
      stream.first = B.elem[0];
    }
    datafile.updateA(stream, p);
    datafile.updateB(B, stream.blockpos);
    datafile.Cl();
    if (B.size >= BLOCKSIZE) {
      datafile.Op();
      BREAK(stream, B);
      datafile.updateA(stream, p);
      datafile.updateB(B, stream.blockpos);
      datafile.Cl();
    }
  }
}

inline void database::Delete(const string &ind, const int &val) {
  if (empt) {
    return;
  }
  datafile.Op();
  char index[64] = {};
  TurnType(ind, index);
  partA A;
  partB B;
  int p = sizeof(int), lastp = p;
  partA stream;
  datafile.readA(stream, p);
  while (!RUN(val, stream, index)) {
    lastp = p;
    p = stream.next;
    datafile.readA(stream, p);
  }
  datafile.readB(B, stream.blockpos);
  DELETE(val, B, index);
  if (checkbeg) {
    stream.first = B.elem[0];
  }
  datafile.updateA(stream, p);
  datafile.updateB(B, stream.blockpos);
  datafile.Cl();
  if (B.size <= 0) {
    partA bef;
    datafile.Op();
    if (p != sizeof(int)) {
      datafile.readA(bef, lastp);
      bef.next = stream.next;
      datafile.updateA(bef, lastp);
    } else {
      if (stream.next == -1) {
        datafile.write_info(0);
        empt = true;
        // std::cout<<"YEP\n";
      } else {
        // std::cout << "IN\n";
        datafile.readA(bef, stream.next);
        stream = bef;
        datafile.updateA(stream, p);
        // std::cout<<stream.blockpos<<" "<<bef.blockpos<<'\n';
        //  datafile.updateA(stream,p);
      }
    }
    datafile.Cl();
  }
}
inline int Find_FIR(const partB &block, const char (&index)[64]) {
  int l = 0, r = block.size - 1, mid;
  while (l < r) {
    mid = (l + r) / 2;
    if (MyCompareS(block.elem[mid].index, index)) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  if (!MyCompareE(block.elem[r].index, index)) {
    return -1;
  }
  return r;
}
inline int Find_LAS(const partB &block, const char (&index)[64]) {
  int l = 0, r = block.size - 1, mid;
  while (l < r) {
    mid = (l + r + 1) / 2;
    if (MyCompareL(block.elem[mid].index, index)) {
      r = mid - 1;
    } else {
      l = mid;
    }
  }
  return l;
}
inline void PRINT_BLOCK(const partB &block, const char (&index)[64]) {
  outflag = false;
  int beg = Find_FIR(block, index);
  int end = Find_LAS(block, index);
  if (beg != -1) {
    outflag = true;
    // std::cout<<"beg: "<<beg<<" end: "<<end<<'\n';
    for (int i = beg; i <= end; i++) {
      std::cout << block.elem[i].value << " ";
    }
  }
}
inline void database::Find(const std::string &ind) {
  if (empt) {
    std::cout << "null\n";
    return;
  } else {
    datafile.Op();
    int p = sizeof(int), lastp = p;
    char index[64] = {};
    TurnType(ind, index);
    partA stream;
    partB B;
    datafile.readA(stream, p);
    while (MyCompareS(stream.first.index, index)) {
      lastp = p;
      p = stream.next;
      if (p == -1) {
        break;
      }
      datafile.readA(stream, p);
    }
    datafile.readA(stream, lastp);
    datafile.readB(B, stream.blockpos);
    PRINT_BLOCK(B, index);
    if (stream.next == -1) {
      if (outflag)
        std::cout << '\n';
      if (!outflag) {
        std::cout << "null\n";
      }
      datafile.Cl();
      return;
    }
    datafile.readA(stream, stream.next);
    if (MyCompareL(stream.first.index, index)) {
      if (outflag)
        std::cout << '\n';
      if (!outflag) {
        std::cout << "null\n";
      }
      datafile.Cl();
      return;
    }
    while (MyCompareE(stream.first.index, index)) {
      datafile.readB(B, stream.blockpos);
      PRINT_BLOCK(B, index);
      if (stream.next == -1) {
        std::cout << '\n';
        datafile.Cl();
        return;
      }
      datafile.readA(stream, stream.next);
    }
    std::cout << '\n';
    datafile.Cl();
  }
}

inline void database::BREAK(partA &A, partB &B) {
  partA nextA;
  partB nextB;
  nextB.size = 0;
  nextA.next = A.next;
  data tmp;
  int num = B.size - BLOCKSIZE / 2;
  for (int i = 0; i < BLOCKSIZE / 2; i++) {
    nextB.elem[i] = B.elem[num + i];
    B.elem[num + i] = tmp;
    B.size--;
    nextB.size++;
  }
  nextA.first = nextB.elem[0];
  nextA.blockpos = datafile.writeB(nextB);
  A.next = datafile.writeA(nextA);
}

inline void database::StreamPrint() {
  if (empt) {
    std::cout << "NOW EMPTY\n";
  } else {
    datafile.Op();
    int p = sizeof(int), lastp = p;
    partA stream;
    partB seeB;
    datafile.readA(stream, p);
    while (true) {
      datafile.readB(seeB, stream.blockpos);
      for (int i = 0; i < seeB.size; i++) {
        std::cout << "Value: " << seeB.elem[i].value << " | Index:";
        for (int j = 0; j < 64; j++) {
          if (seeB.elem[i].index[j] == '\0') {
            break;
          }
          std::cout << seeB.elem[i].index[j];
        }
        std::cout << '\n';
      }
      std::cout << "|BLOCK OVER|\n";
      p = stream.next;
      if (p == -1) {
        break;
      }
      datafile.readA(stream, p);
    }
    datafile.Cl();
  }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main() {
  int n;
  std::cin >> n;
  std::string statment, ind;
  int val;
  database ans("finalword");
  for (int i = 0; i < n; i++) {
    // std::cout<<i<<'\n';
    std::cin >> statment;
    if (statment == "insert") {
      std::cin >> ind >> val;
      ans.Insert(ind, val);
    } else if (statment == "delete") {
      std::cin >> ind >> val;
      ans.Delete(ind, val);
    } else if (statment == "find") {
      std::cin >> ind;
      ans.Find(ind);
    } else if (statment == "look") {
      std::cout << "LIST:\n";
      ans.StreamPrint();
    }
  }
  return 0;
}