#include <iomanip>
#include <iostream>
#include <system/console.hpp>

int main() {
  for (int i = (int)common::Color::BLACK; i <= (int)common::Color::WHITE; ++i) {
    for (int j = (int)common::Color::BLACK; j < (int)common::Color::COUNT; ++j) {
      std::cout << std::make_pair((common::Color)i, (common::Color)j);
      std::cout << " ";
      std::cout << std::setfill('0') << std::setw(2) << i;
      std::cout << " / ";
      std::cout << std::setfill('0') << std::setw(2) << j;
      std::cout << " ";
      common::Console::SetColor(common::Color::WHITE, common::Color::BLACK);
    }
    std::cout << std::endl;
  }
  return 0;
}
