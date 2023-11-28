#include <cstddef>
#include <iostream>
#include "2074.hpp"

int main() {
  int n;
  std::cin >> n;
  std::string statment, ind;
  int val;
  kv_database ans;
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