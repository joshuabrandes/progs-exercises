
#include <iostream>

int& foo() {
  int x = 2;
  return x;
}

int bar() {
  int a = 42;
  return a;
}

int main() {

  int& x = foo();
  int y = bar();

  std::cout << x << std::endl;

  return 0;
}
