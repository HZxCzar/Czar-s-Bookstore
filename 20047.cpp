#include <cstdarg>
#include <cstddef>
#include <fstream>
#include <iostream>
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
constexpr int BLOCKSIZE = 800;
bool check = false;
struct indexblock {
  int last = -1;
  int next = -1;
  char index[64] = {};
  int blockpos = 0;
  int flag = -1;
  int maxi = -1;
  int mini = 11451400;
};
struct valueblock {
  int elem[BLOCKSIZE * 2][2] = {0};
  int size = 0;
  int flagsize = 0;
};
template <class indexblock, class valueblock> class MemoryRiver {
private:
  fstream file;
  string file_name;
  int sizeofi = sizeof(indexblock);
  int sizeofv = sizeof(valueblock);

public:
  MemoryRiver() = default;
  MemoryRiver(const string &file_name) : file_name(file_name) {}
  void Op() { file.open(file_name, std::ios::in | std::ios::out); }
  void Cl() { file.close(); }
  void Setfile(const string &name) { file_name = name; }
  void initialise() {
    file.open(file_name, std::ios::out);
    indexblock tmp;
    int beg = 0;
    file.write(reinterpret_cast<char *>(&beg), sizeof(int));
    for (int i = 0; i < 1145; ++i) {
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
    file.seekp(0);
    file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
  }
  //在文件合适位置写入类对象t，并返回写入的位置索引index
  //位置索引意味着当输入正确的位置索引index，在以下三个函数中都能顺利的找到目标对象进行操作
  //位置索引index可以取为对象写入的起始位置
  int write(indexblock &t) {
    file.close();
    file.open(file_name, std::ios::out | std::ios::in);
    int num;
    get_info(num);
    int pos = num * sizeofi + sizeof(int);
    file.seekp(pos);
    file.write(reinterpret_cast<char *>(&t), sizeofi);
    write_info(num + 1);
    return pos;
  }
  int write(valueblock &t) {
    file.close();
    file.open(file_name, std::ios::out | std::ios::in | std::ios::ate);
    int pos = file.tellp();
    file.write(reinterpret_cast<char *>(&t), sizeofv);
    return pos;
  }

  //用t的值更新位置索引index对应的对象，保证调用的index都是由write函数产生
  void update(indexblock &t, const int index) {
    file.seekp(index);
    file.write(reinterpret_cast<char *>(&t), sizeofi);
  }
  void update(valueblock &t, const int index) {
    file.seekp(index);
    file.write(reinterpret_cast<char *>(&t), sizeofv);
  }

  //读出位置索引index对应的T对象的值并赋值给t，保证调用的index都是由write函数产生
  void read1(indexblock &t, const int index) {
    file.seekg(index);
    file.read(reinterpret_cast<char *>(&t), sizeofi);
  }
  void read2(valueblock &t, const int index) {
    file.seekg(index);
    file.read(reinterpret_cast<char *>(&t), sizeofv);
  }

  //删除位置索引index对应的对象(不涉及空间回收时，可忽略此函数)，保证调用的index都是由write函数产生
  void Delete(int index) { /* your code here */
  }
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`

class iv_database {
public:
  iv_database() = default;
  iv_database(const string &name);
  //插入index数据value
  void Insert(const string &ind, const int &val);
  //删除index数据value，可能不存在
  void Delete(const string &ind, const int &val);
  //找到index（可能不存在，则输出null），并升序输出
  void Find(const std::string &ind);
  bool INTHISPART(const int &val, const indexblock &block, const string &str);
  void BREAK(indexblock &first);

private:
  //二分查找value
  int BinarySearch(const int &val, const valueblock &block, const int &flag);
  //添加value
  void ADD(const int &val, valueblock &block, const int &flag);
  //删除pos
  void DELETE(const int &val, valueblock &block, const int &flag);
  MemoryRiver<indexblock, valueblock> datafile;
  bool empt = false;
};

inline int FIND_FIRST(const valueblock &block, const int &flag) {
  int left = 0, right = block.size - 1, mid, checkflag;
  while (left < right) {
    mid = (left + right) / 2;
    checkflag = block.elem[mid][1];
    if (checkflag < flag) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  return right;
}
inline int FIND_LAST(const valueblock &block, const int &flag) {
  int left = 0, right = block.size - 1, mid, checkflag;
  while (left < right) {
    mid = (left + right + 1) / 2;
    checkflag = block.elem[mid][1];
    if (checkflag <= flag) {
      left = mid;
    } else {
      right = mid - 1;
    }
  }
  return right;
}

inline void PRINT_FLAG(const valueblock &block, const int &flag) {
  int right = FIND_FIRST(block, flag);
  for (int i = right; i < block.size; i++) {
    if (block.elem[i][1] != flag) {
      return;
    } else {
      std::cout << block.elem[i][0] << " ";
      // std::cout << block.elem[i][1] << " <flag ";
    }
  }
}

inline void TurnType(const string &str, char (&elem)[64]) {
  for (int i = 0; i < str.size(); i++) {
    elem[i] = str[i];
  }
}

inline iv_database::iv_database(const string &name) {
  datafile.Setfile(name);
  // datafile.Clear();
  if (datafile.IS_FIRST_OPEN()) {
    // std::cout<<"FIRST\n";
    empt = true;
    datafile.initialise();
  } else {
    datafile.Op();
    int tmp;
    datafile.get_info(tmp);
    // std::cout<<tmp<<'\n';
    if (tmp == 0) {
      // std::cout<<"SECOND\n";
      datafile.initialise();
      datafile.write_info(0);
      empt = true;
    }
    datafile.Cl();
  }
}

inline int iv_database::BinarySearch(const int &val, const valueblock &block,
                                     const int &flag) {
  int left = 0, right = block.size - 1, mid, value, checkflag;
  while (left < right) {
    mid = (left + right) / 2;
    checkflag = block.elem[mid][1];
    if (checkflag < flag) {
      left = mid + 1;
    } else if (checkflag > flag) {
      right = mid - 1;
    } else {
      value = block.elem[mid][0];
      if (value < val) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
  }
  return right;
}

inline void iv_database::ADD(const int &val, valueblock &block,
                             const int &flag) {
  if (flag > block.flagsize) {
    block.flagsize = flag;
    block.elem[block.size][0] = val;
    block.elem[block.size][1] = flag;
    block.size++;
  }
  int pos = BinarySearch(val, block, flag);
  int checknum = block.elem[pos][0];
  if (val > checknum) {
    for (int i = block.size; i > pos + 1; i--) {
      block.elem[i][0] = block.elem[i - 1][0];
      block.elem[i][1] = block.elem[i - 1][1];
    }
    block.size++;
    block.elem[pos + 1][0] = val;
    block.elem[pos + 1][1] = flag;
    // std::cout << "pos:" << pos + 1 << '\n';
  } else {
    if (val == checknum) {
      return;
    }
    for (int i = block.size; i > pos; i--) {
      block.elem[i][0] = block.elem[i - 1][0];
      block.elem[i][1] = block.elem[i - 1][1];
    }
    block.size++;
    block.elem[pos][0] = val;
    block.elem[pos][1] = flag;
  }
}

inline void iv_database::DELETE(const int &val, valueblock &block,
                                const int &flag) {
  check = false;
  if (flag > block.flagsize) {
    return;
  }
  int pos = BinarySearch(val, block, flag);
  if (block.elem[pos][1] != flag) {
    return;
  }
  int checknum = block.elem[pos][0];
  if (val > checknum) {
    return;
  } else {
    if (val == block.elem[pos][0]) {
      for (int i = pos; i < block.size; i++) {
        block.elem[i][0] = block.elem[i + 1][0];
        block.elem[i][1] = block.elem[i + 1][1];
      }
      block.size--;
      if (block.elem[pos][1] != flag) {
        if ((pos < 1 || block.elem[pos - 1][1] != flag) &&
            (pos >= block.size - 1 || block.elem[pos + 1][1] != flag)) {
          check = true;
        }
      }
    }
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

inline bool iv_database::INTHISPART(const int &val, const indexblock &block,
                                    const string &str) {
  if (!EQUAL(block.index, str)) {
    return false;
  } else {
    if (val <= block.maxi) {
      return true;
    }
    int nextp = block.next;
    if (nextp != -1) {
      indexblock nextblock;
      datafile.read1(nextblock, nextp);
      if (EQUAL(nextblock.index, str)) {
        if (val >= nextblock.mini) {
          return false;
        }
      }
    }
    return true;
  }
}

inline void iv_database::Insert(const string &ind, const int &val) {
  datafile.Op();
  indexblock indblock;
  valueblock valblock;
  if (empt) {
    TurnType(ind, indblock.index);
    indblock.flag = 1;
    indblock.next = -1;
    datafile.write(indblock);
    indblock.blockpos = datafile.write(valblock);
    ADD(val, valblock, indblock.flag);
    indblock.maxi = val;
    indblock.mini = val;
    empt = false;
    datafile.update(indblock, sizeof(int));
    datafile.update(valblock, indblock.blockpos);
    datafile.Cl();
    return;
  } else {
    int p = sizeof(int), lastp = p;
    indexblock stream;
    datafile.read1(stream, p);
    while (!INTHISPART(val, stream, ind)) {
      lastp = p;
      p = stream.next;
      datafile.read1(stream, p);
      datafile.Cl();
      datafile.Op();
      if (p == -1) {
        break;
      }
    }
    if (p == -1) {
      datafile.read1(stream, lastp);
      datafile.read2(valblock, stream.blockpos);
      TurnType(ind, indblock.index);
      indblock.blockpos = stream.blockpos;
      indblock.flag = valblock.flagsize + 1;
      ADD(val, valblock, indblock.flag);
      indblock.last = lastp;
      indblock.maxi = val;
      indblock.mini = val;
      indblock.next = -1;
      stream.next = datafile.write(indblock);
      datafile.update(stream, indblock.last);
      datafile.update(valblock, stream.blockpos);
      // std::cout<<"size:"<<valblock.size<<'\n';
      datafile.Cl();
      if (valblock.size >= BLOCKSIZE) {
        datafile.Op();
        BREAK(indblock);
        datafile.update(indblock, stream.next);
        datafile.Cl();
      }
    } else {
      datafile.read2(valblock, stream.blockpos);
      ADD(val, valblock, stream.flag);
      if (val > stream.maxi) {
        stream.maxi = val;
      }
      if (val < stream.mini) {
        stream.mini = val;
      }
      datafile.update(stream, p);
      datafile.update(valblock, stream.blockpos);
      datafile.Cl();
      if (valblock.size >= BLOCKSIZE) {
        datafile.Op();
        // std::cout << "TEST BREAK2\n";
        BREAK(stream);
        datafile.update(stream, p);
        datafile.Cl();
      }
    }
  }
}

inline void iv_database::Delete(const string &ind, const int &val) {
  datafile.Op();
  indexblock indblock;
  valueblock valblock;
  if (empt) {
    datafile.Cl();
    return;
  } else {
    int p = sizeof(int), lastp = p;
    indexblock stream;
    datafile.read1(stream, p);
    while (!INTHISPART(val, stream, ind)) {
      lastp = p;
      p = stream.next;
      datafile.read1(stream, p);
      if (p == -1) {
        break;
      }
    }
    if (p == -1) {
      datafile.Cl();
      return;
    } else {
      datafile.read2(valblock, stream.blockpos);
      DELETE(val, valblock, stream.flag);
      datafile.update(valblock, stream.blockpos);
      if (check) {
        indexblock repla;
        if (p != sizeof(int)) {
          datafile.read1(repla, lastp);
          repla.next = stream.next;
          datafile.update(repla, lastp);
        } else {
          if (stream.next == -1) {
            datafile.write_info(0);
            empt = true;
          } else {
            datafile.read1(repla, stream.next);
            for (int i = 0; i < 64; i++) {
              stream.index[i] = repla.index[i];
            }
            stream.next = repla.next;
            stream.flag = repla.flag;
            stream.blockpos = repla.blockpos;
            stream.maxi = repla.maxi;
            stream.mini = repla.mini;
            datafile.update(stream, p);
          }
        }
      }
      datafile.Cl();
    }
  }
}

inline void iv_database::Find(const std::string &ind) {
  if (empt) {
    std::cout << "null\n";
    return;
  } else {
    datafile.Op();
    int p = sizeof(int), lastp = p;
    indexblock stream;
    datafile.read1(stream, p);
    while (!EQUAL(stream.index, ind)) {
      lastp = p;
      p = stream.next;
      datafile.read1(stream, p);
      if (p == -1) {
        break;
      }
    }
    if (p == -1) {
      std::cout << "null\n";
      datafile.Cl();
      return;
    } else {
      valueblock valblock;
      datafile.read2(valblock, stream.blockpos);
      PRINT_FLAG(valblock, stream.flag);
      p = stream.next;
      if (p == -1) {
        std::cout << '\n';
        datafile.Cl();
        return;
      }
      datafile.read1(stream, p);
      while (EQUAL(stream.index, ind)) {
        // std::cout<<"checknext\n";
        datafile.read2(valblock, stream.blockpos);
        PRINT_FLAG(valblock, stream.flag);
        p = stream.next;
        if (p == -1) {
          std::cout << '\n';
          datafile.Cl();
          return;
        }
        datafile.read1(stream, p);
      }
      std::cout << '\n';
      datafile.Cl();
    }
  }
}

inline void iv_database::BREAK(indexblock &first) {
  // std::cout<<"BREAK!\n";
  valueblock valblock;
  datafile.read2(valblock, first.blockpos);
  int beg = FIND_FIRST(valblock, first.flag);
  int end = FIND_LAST(valblock, first.flag);
  valueblock newblock;
  newblock.flagsize = 1;
  // std::cout<<"size:"<<valblock.size<<'\n';
  int num = end - beg + 1;
  // std::cout<<"num:"<<num<<'\n';
  for (int i = 0; i < num; i++) {
    newblock.elem[i][0] = valblock.elem[i + beg][0];
    newblock.elem[i][1] = 1;
    valblock.elem[i + beg][0] = 0;
    valblock.elem[i + beg][1] = 0;
  }
  for (int i = 0; i < valblock.size - end - 1; i++) {
    valblock.elem[i + beg][0] = valblock.elem[i + end][0];
    valblock.elem[i + beg][1] = valblock.elem[i + end][1];
  }
  valblock.size -= num;
  newblock.size = num;
  datafile.update(valblock, first.blockpos);
  first.blockpos = datafile.write(newblock);
  first.flag = 1;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main() {
  int n;
  std::cin >> n;
  std::string statment, ind;
  int val;
  iv_database ans("filename");
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
  return 0;
}