#include <utils/time_of_day.hpp>
#include <iostream>

int main() {
  utils::datetime::TimeOfDay<std::chrono::seconds> tod {"10:20:30"};
  std::cout << tod.Hours() << std::endl;
  std::cout << tod.Minutes() << std::endl;
  std::cout << tod.Seconds() << std::endl;
  std::cout << tod.Subseconds().count();

  return 0;
}
