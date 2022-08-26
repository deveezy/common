#include <pthread.h>
#include <system/environment.hpp>
#include <iostream>

int main() {
  // std::cout << common::Environment::OSVersion();
  const auto res = common::Environment::envars();
  for (const auto &elem : res) {
    std::cout << elem.first << "=" << elem.second << "\n";
  }
  return 0;
}
