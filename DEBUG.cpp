#include <cstddef>
#include <fstream>
#include <iostream>
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
constexpr int BLOCKSIZE = 300;
template <class T> class MemoryRiver {
private:
  fstream file;
  string file_name;
  int sizeofT = sizeof(T);

public:
  MemoryRiver() = default;

  MemoryRiver(const string &file_name) : file_name(file_name) {}
  void check()
  {
    if(file.is_open())
    {
      std::cout<<"open\n";
    }
    else
    {
      std::cout<<"not\n";
    }
  }
  void Op()
  {
    file.open(file_name,std::ios::in | std::ios::out);
  }
  void Cl()
  {
    file.close();
  }
  void Setfile(const string &name) { file_name = name; }
  void Clear()
  {
    file.open(file_name,std::ios::out);
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
  //在文件合适位置写入类对象t，并返回写入的位置索引index
  //位置索引意味着当输入正确的位置索引index，在以下三个函数中都能顺利的找到目标对象进行操作
  //位置索引index可以取为对象写入的起始位置
  int write(T &t) {
    file.close();
    file.open(file_name, std::ios::out | std::ios::in | std::ios::ate);
    int pos = file.tellp();
    file.write(reinterpret_cast<char *>(&t), sizeofT);
    return pos;
  }

  //用t的值更新位置索引index对应的对象，保证调用的index都是由write函数产生
  void update(T &t, const int index) {
    //file.open(file_name, std::ios::out | std::ios::in);
    file.seekp(index);
    file.write(reinterpret_cast<char *>(&t), sizeofT);
    //file.close();
  }

  //读出位置索引index对应的T对象的值并赋值给t，保证调用的index都是由write函数产生
  void read(T &t, const int index) {
    //file.open(file_name, std::ios::in);
    file.seekg(index);
    file.read(reinterpret_cast<char *>(&t), sizeofT);
    //file.close();
  }

  //删除位置索引index对应的对象(不涉及空间回收时，可忽略此函数)，保证调用的index都是由write函数产生
  void Delete(int index) { /* your code here */
  }
};
//~~~~~~~~~~~~~~~~~~~~
struct data {
  int next = -1;
  int elem[BLOCKSIZE + 10] = {0};
  char index[64] = {};
  int size = 0;
};
//~~~~~~~~~~~~~~~~~~~~
class kv_database {
public:
  kv_database() = default;
  kv_database(const string &name);
  //插入index数据value
  void Insert(std::string &, const int &);
  //删除index数据value，可能不存在
  void Delete(const std::string &, const int &);
  //找到index（可能不存在，则输出null），并升序输出
  void Find(const std::string &);
  bool INTHISPART(const int &val, const data &here, const string &str);
  void BREAK(data &, const int &);
private:
  //二分查找value
  int BinarySearch(const int &val, const data &block);
  //添加value
  void ADD(const int &val, data &block);
  //删除pos
  void DELETE(const int &val, data &block);
  MemoryRiver<data> datafile;
  bool empt = false;
};

inline void TurnType(const string &str, char (&elem)[64]) {
  for (int i = 0; i < str.size(); i++) {
    elem[i] = str[i];
  }
}

inline kv_database::kv_database(const string &name) {
  datafile.Setfile(name);
  //datafile.Clear();
  if (datafile.IS_FIRST_OPEN()) {
    empt = true;
  } else {
    data test;
    datafile.Op();
    datafile.read(test, 0);
    if (test.size == 0) {
      empt = true;
    }
    datafile.Cl();
  }
}

inline void kv_database::BREAK(data &here, const int &p) {
  data newblock;
  for (int i = 0; i < 64; i++) {
    newblock.index[i] = here.index[i];
  }
  int num=here.size;
  for (int i = BLOCKSIZE / 2; i < num; i++) {
    newblock.elem[newblock.size] = here.elem[i];
    here.elem[i] = 0;
    here.size--;
    newblock.size++;
  }
  newblock.next = here.next;
  here.next = datafile.write(newblock);
  datafile.update(here, p);
}

inline int kv_database::BinarySearch(const int &val, const data &block) {
  int left = 0, right = block.size, mid, value;
  while (left < right) {
    mid = (left + right) / 2;
    value = block.elem[mid];
    if (value < val) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  return right;
}

inline void kv_database::DELETE(const int &val, data &block) {
  int l = 0, r = block.size;
  if (r <= 0)
    return;
  int checkelem = block.elem[r - 1];
  if (val > checkelem) {
    return;
  } else {
    int p = BinarySearch(val, block);
    if (val == block.elem[p]) {
      for (int i = p; i < r; i++) {
        block.elem[i] = block.elem[i + 1];
      }
      block.size--;
    }
  }
}

inline void kv_database::ADD(const int &val, data &block) {
  int l = 0, r = block.size;
  if (r <= 0) {
    block.elem[r] = val;
    block.size++;
  }
  int checknum;
  checknum = block.elem[r - 1];
  if (val > checknum) {
    block.elem[r] = val;
    block.size++;
    return;
  } else {
    int p = BinarySearch(val, block);
    checknum = block.elem[p];
    if (checknum == val) {
      return;
    }
    for (int i = r-1; i >=p; i--) {
      block.elem[i + 1] = block.elem[i];
    }
    block.elem[p] = val;
    block.size++;
  }
}
inline bool EQUAL(const char (&elem)[64], const string &str) {
  for (int i = 0; i < str.size(); i++) {
    if (elem[i] != str[i]) {
      return false;
    }
  }
  if (elem[str.size()] != '\0') {
    return false;
  }
  return true;
}

inline bool kv_database::INTHISPART(const int &val, const data &here,
                                    const string &str) {
  if (!EQUAL(here.index, str)) {
    return false;
  } else {
    if(val<=here.elem[here.size-1])
    {
      return true;
    }
    int nextp = here.next;
    if (nextp != -1) {
      data fol;
      datafile.read(fol, nextp);
      if (EQUAL(fol.index, str)) {
        if (val >= fol.elem[0]) {
          return false;
        }
      }
    }
    return true;
  }
}

inline void kv_database::Insert(std::string &ind, const int &val) {
  datafile.Op();
  data ins;
  if (empt) {
    TurnType(ind, ins.index);
    ins.size = 1;
    ins.elem[0] = val;
    ins.next = -1;
    datafile.update(ins,0);
    empt = false;
    datafile.Cl();
    return;
  } else {
    int p = 0, lastp = 0;
    data h;
    datafile.read(h, p);
    while (!INTHISPART(val, h, ind)) {
      lastp = p;
      p = h.next;
      datafile.read(h, p);
      if (p == -1) {
        break;
      }
    }
    if (p == -1) {
      datafile.read(h, lastp);
      ins.size = 1;
      TurnType(ind, ins.index);
      ins.elem[0] = val;
      int pos = datafile.write(ins);
      h.next = pos;
      datafile.update(h, lastp);
    } else {
      ADD(val, h);
      datafile.update(h, p);
      if (h.size == BLOCKSIZE) {
        BREAK(h, p);
      }
    }
    datafile.Cl();
  }
}

inline void kv_database::Delete(const std::string &ind, const int &val) {
  datafile.Op();
  data ins;
  if (empt) {
    datafile.Cl();
    return;
  } else {
    int p = 0, lastp = 0;
    data h;
    datafile.read(h, p);
    while (!INTHISPART(val, h, ind)) {
      lastp = p;
      p = h.next;
      datafile.read(h, p);
      if (p == -1) {
        break;
      }
    }
    if (p == -1) {
      datafile.Cl();
      return;
    } else {
      DELETE(val, h);
      datafile.update(h, p);
      if (h.size == 0) {
        if (p != 0) {
          data lastblock;
          datafile.read(lastblock, lastp);
          lastblock.next = h.next;
          datafile.update(lastblock, lastp);
        } else {
          if (h.next == -1) {
            empt = true;
          } else {
            data nextblock;
            datafile.read(nextblock, h.next);
            for (int i = 0; i < 64; i++) {
              h.index[i] = nextblock.index[i];
            }
            for (int i = 0; i < nextblock.size; i++) {
              h.elem[i] = nextblock.elem[i];
            }
            h.size = nextblock.size;
            h.next = nextblock.next;
            datafile.update(h, p);
          }
        }
      }
      datafile.Cl();
    }
  }
}

inline void kv_database::Find(const std::string &ind) {
  if (empt) {
    std::cout << "null\n";
    return;
  } else {
    datafile.Op();
    int p = 0, lastp = 0;
    data h;
    datafile.read(h, p);
    while (!EQUAL(h.index, ind)) {
      lastp = p;
      p = h.next;
      datafile.read(h, p);
      if (p == -1) {
        break;
      }
    }
    if (p == -1) {
      std::cout << "null\n";
      datafile.Cl();
      return;
    } else {
      for (int i = 0; i < h.size; i++) {
        std::cout << h.elem[i] << " ";
      }
      p = h.next;
      if (p == -1) {
        std::cout << '\n';
        datafile.Cl();
        return;
      }
      datafile.read(h, p);
      while (EQUAL(h.index, ind)) {
        for (int i = 0; i < h.size; i++) {
          std::cout << h.elem[i] << " ";
        }
        p = h.next;
        if (p == -1) {
          std::cout << '\n';
          datafile.Cl();
          return;
        }
        datafile.read(h, p);
      }
      std::cout << '\n';
      datafile.Cl();
    }
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main() {
  int n;
  std::cin >> n;
  std::string statment, ind;
  int val;
  kv_database ans("testcase");
  for (int i = 0; i < n; i++) {
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
    }
  }
  //ans.END();
  return 0;
}