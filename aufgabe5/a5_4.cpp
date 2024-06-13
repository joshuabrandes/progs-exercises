
#include <iostream>

class Foo {
public:
  Foo() {};
  void setVal(float f) { f_ = f; }
private:
  float f_;
};

void someFunction(float f) {
  Foo x();
  x.setVal(f);
}

int main() {
  someFunction(2.3);

  return 0;
}

