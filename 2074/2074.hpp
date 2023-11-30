#ifndef _2074_HPP_
#define _2074_HPP_

#include "MemoryRiver.hpp"
#include <cstddef>
#include <cstring>
#include <iostream>
#include <string>
constexpr int s = sizeof(int);
constexpr int headindex = 150000 * s;

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

  void CHECK(int pos);

private:
  //二分查找value
  int BinarySearch(const int &val, const int &l, const int &r);
  //添加value
  void ADD(const int &val, const int &l, int &r);
  //删除pos
  void DELETE(const int &val, const int &l, int &r);
  // bool IS_EMPTY() { return !size; }
  MemoryRiver<char[64], 150000> datafile;
};

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

inline void TurnType(const string &str, char (&elem)[64]) {
  for (int i = 0; i < str.size(); i++) {
    elem[i] = str[i];
  }
}

inline void kv_database::CHECK(int pos) {
  char elem[64];
  datafile.read(elem, pos);
  std::cout << elem[0] << elem[1] << elem[2] << elem[3] << '\n';
}

inline int kv_database::BinarySearch(const int &val, const int &l,
                                     const int &r) {
  int left = l, right = r, mid, value;
  while (left < right) {
    mid = (left + right) / 2;
    datafile.get_info(value, mid);
    if (value < val) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  return right;
}

inline void kv_database::DELETE(const int &val, const int &l, int &r) {
  if (l >= r)
    return;
  int checkelem;
  datafile.get_info(checkelem, r - 1);
  if (val > checkelem) {
    return;
  } else {
    int pos = BinarySearch(val, l, r);
    datafile.get_info(checkelem, pos);
    if (checkelem == val) {
      int tmp;
      for (int i = pos; i < r; i++) {
        datafile.get_info(tmp, i + 1);
        datafile.write_info(tmp, i);
      }
      //传地址，修改原处
      r--;
    }
  }
}

// l为开始处，r为最后一个数据下一个的pos
inline void kv_database::ADD(const int &val, const int &l, int &r) {
  if (l >= r) {
    datafile.write_info(val, r);
    r++;
    return;
  }
  int checkelem;
  datafile.get_info(checkelem, r - 1);
  if (val > checkelem) {
    datafile.write_info(val, r);
    r++;
    return;
  } else {
    int pos = BinarySearch(val, l, r);
    datafile.get_info(checkelem, pos);
    if (checkelem == val) {
      return;
    }
    int tmp;
    for (int i = pos; i < r; i++) {
      datafile.get_info(tmp, i);
      datafile.write_info(tmp, i + 1);
    }
    datafile.write_info(val, pos);
    r++;
  }
}

inline kv_database::kv_database(const string &name) {
  datafile.Setfile(name);
  // if (datafile.IS_FIRST_OPEN()) {
  // std::cout<<"in\n";
  datafile.initialise();
  datafile.write_info(-1, 1);
  //}
}

inline void kv_database::Find(const std::string &ind) {
  int checknum;
  datafile.get_info(checknum, 1);
  if (checknum == -1) {
    std::cout << "null\n";
    return;
  } else {
    int pos = 1;
    char index[64] = {};
    datafile.read(index, checknum);
    while (!EQUAL(index, ind)) {
      datafile.get_info(pos, pos + 3);
      if (pos == -1) {
        break;
      }
      datafile.get_info(checknum, pos);
      datafile.read(index, checknum);
    }
    if (pos == -1) {
      std::cout << "null\n";
      return;
    } else {
      int l, r;
      datafile.get_info(l, pos + 1);
      datafile.get_info(r, pos + 2);
      for (int i = l; i < r; i++) {
        datafile.get_info(checknum, i);
        std::cout << checknum << " ";
      }
      std::cout << '\n';
    }
  }
}

inline void kv_database::Insert(std::string &ind, const int &val) {
  int checknum;
  datafile.get_info(checknum, 1);
  char index[64] = {};
  if (checknum == -1) {
    TurnType(ind, index);
    checknum = datafile.write(index);
    datafile.write_info(checknum, 1);
    datafile.write_info(val, 20000);
    datafile.write_info(20000, 2);
    datafile.write_info(20001, 3);
    datafile.write_info(-1, 4);
    return;
  } else {
    int pos = 1, last_pos;
    datafile.read(index, checknum);
    while (!EQUAL(index, ind)) {
      last_pos = pos;
      datafile.get_info(pos, pos + 3);
      if (pos == -1) {
        break;
      }
      datafile.get_info(checknum, pos);
      datafile.read(index, checknum); //存错东西了
    }
    if (pos == -1) {
      pos = last_pos;
      datafile.write_info(pos + 4, pos + 3);
      char line[64] = {};
      TurnType(ind, line);
      checknum = datafile.write(line);
      datafile.write_info(checknum, pos + 4);
      pos += 4;
      int l, r;
      l = ((pos - 1) / 4 * 20 + 20000);
      r = l;
      datafile.write_info(l, pos + 1);
      datafile.write_info(r, pos + 2);
      datafile.write_info(-1, pos + 3);
      ADD(val, l, r);
      datafile.write_info(r, pos + 2); //修改r值
    } else {
      int l, r;
      datafile.get_info(l, pos + 1);
      datafile.get_info(r, pos + 2);
      ADD(val, l, r);
      datafile.write_info(r, pos + 2); //修改r值
    }
  }
}

inline void kv_database::Delete(const std::string &ind, const int &val) {
  int checknum;
  datafile.get_info(checknum, 1);
  if (checknum == -1) {
    return;
  } else {
    int pos = 1, last_pos;
    char index[64] = {};
    datafile.read(index, checknum);
    while (!EQUAL(index, ind)) {
      last_pos = pos;
      datafile.get_info(pos, pos + 3);
      if (pos == -1) {
        break;
      }
      datafile.get_info(checknum, pos);
      datafile.read(index, checknum);
    }
    if (pos == -1) {
      return;
    } else {
      int l, r;
      datafile.get_info(l, pos + 1);
      datafile.get_info(r, pos + 2);
      DELETE(val, l, r);
      datafile.write_info(r, pos + 2); //修改r值
      if (l == r) {
        if (pos == 1) {
          //后面贴到前面
          //改pos(4)-1
          datafile.get_info(pos, pos + 3);
          if (pos == -1) {
            datafile.write_info(-1, 1);
          } else {
            datafile.get_info(checknum, pos);
            datafile.write_info(checknum, 1);
            datafile.get_info(checknum, pos + 3);
            datafile.write_info(checknum, 4);
          }
        } else {
          datafile.get_info(checknum, pos + 3);
          datafile.write_info(checknum, last_pos + 3);
        }
      }
    }
  }
}

#endif