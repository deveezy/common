#include <common/function.hpp>
#include <iostream>

int test(int v) { return v + 100; }

class Foo
{
public:
  int operator()(int _v) { return _v + 200; }
  int test(int _v) { return _v + 300; }
  static int static_test(int _v) { return _v + 400; }
};

int main() {
  common::Function<int(int), 128> function;
  function = test;

  Foo instance;
  function = instance;

  return 0;
}
