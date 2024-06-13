
#include <iostream>

int doStuff() {
  int x = 42;
  int arr[9];

  for (int i = -5; i < 6; ++i) {
    arr[i+4] = i;
  }

  return x;
}

int main() {
  int x = doStuff();
  std::cout << x << std::endl;
  return 0;
}
