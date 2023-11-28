#ifndef _2074_HPP_
#define _2074_HPP_

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
static const int num = 1e6;

struct node {
  //构造
  node() {
    size = 0;
    last = nullptr;
    next = nullptr;
  }
  node(const std::string &ind) { index = ind; }
  //前后指针
  node *last;
  node *next;
  // index
  std::string index;
  //数据长度
  int size;
  //数据内容
  int value[num];
  //二分查找value
  int BinarySearch(const int &val);
  //添加value
  void ADD(const int &val);
  //删除pos
  void DELETE(const int &val);
  bool IS_EMPTY() { return !size; }
};

inline int node::BinarySearch(const int &val) {
  int left = 0, right = size, mid;
  while (left < right) {
    mid = (left + right) / 2;
    if (value[mid] < val) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  return right;
}

inline void node::DELETE(const int &val) {
  if (val > value[size - 1]) {
    return;
  } else {
    int pos = BinarySearch(val);
    if (value[pos] == val) {
      for (int i = pos; i < size; i++) {
        value[i] = value[i + 1];
      }
      value[size - 1] = 0;
      size--;
    }
  }
}

inline void node::ADD(const int &val) {
  if (val > value[size - 1]) {
    value[size++] = val;
  } else {
    int pos = BinarySearch(val);
    if (value[pos] == val)
    {
        return;
    }
    for (int i = pos; i < size; i++) {
      value[i + 1] = value[i];
    }
    value[pos] = val;
    size++;
  }
}

class kv_database {
public:
  kv_database() : head(nullptr) {}
  ~kv_database();
  //插入index数据value
  void Insert(const std::string &, const int &);
  //删除index数据value，可能不存在
  void Delete(const std::string &, const int &);
  //找到index（可能不存在，则输出null），并升序输出
  void Find(const std::string &) const;

private:
  //对应链表头指针
  node *head;
};

inline kv_database::~kv_database() {
  node *tmp = head;
  while (tmp != nullptr) {
    node *t = tmp;
    tmp = tmp->next;
    delete t;
  }
}

inline void kv_database::Find(const std::string &ind) const {
  if (head == nullptr) {
    std::cout << "null\n";
  } else {
    // std::cout<<"IN";
    node *p = head;
    while (p->index != ind) {
      if (p->next != nullptr) {
        p = p->next;
      } else {
        break;
      }
    }
    if (p->index == ind) {
      for (int i = 0; i < p->size; i++) {
        std::cout << p->value[i] << ' ';
      }
      std::cout << '\n';
    } else {
      std::cout << "null\n";
    }
  }
}

inline void kv_database::Insert(const std::string &ind, const int &val) {

  if (head == nullptr) {
    node *tmp = new node(ind);
    tmp->ADD(val);
    head = tmp;
    head->next = nullptr;
  } else {
    node *p = head;
    while (p->index != ind) {
      if (p->next != nullptr) {
        p = p->next;
      } else {
        break;
      }
    }
    if (p->index == ind) {
      p->ADD(val);
    } else {
      node *tmp = new node(ind);
      tmp->ADD(val);
      p->next = tmp;
      tmp->last = p;
      tmp->next = nullptr;
    }
  }
}

inline void kv_database::Delete(const std::string &ind, const int &val) {
  if (head == nullptr) {
    return;
  } else {
    node *p = head;
    while (p->index != ind) {
      if (p->next != nullptr) {
        p = p->next;
      } else {
        break;
      }
    }
    if (p->index == ind) {
      p->DELETE(val);
      if (p->IS_EMPTY()) {
        if (p == head) {
          if (p->next) {
            head = p->next;
          } else {
            head = nullptr;
          }
        } else {
          if (p->last) {
            p->last->next = p->next;
          }
          if (p->next) {
            p->next->last = p->last;
          }
        }

        delete p;
      }
    }
  }
}

#endif