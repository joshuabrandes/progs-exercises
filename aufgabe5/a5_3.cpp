//
//  main.cpp
//  rvalue_stuff
//
//  Created by Matthias Tessmann on 10.11.15.
//  Copyright © 2015 Matthias Tessmann. All rights reserved.
//

#include <iostream>

class Foo {
public:
  Foo() { std::cerr << "foo ctor" << std::endl; }

  Foo(Foo const& rhs)            { std::cerr << "foo copy ctor" << std::endl; }
  Foo(Foo&& rhs)                 { std::cerr << "foo rvalue ctor" << std::endl; }
  Foo& operator=(Foo const& rhs) { std::cerr << "foo copy =" << std::endl; return *this; }
  Foo& operator=(Foo&& rhs)      { std::cerr << "foo rvalue =" << std::endl; return *this; }

};

Foo fn() {
  return Foo();
}

Foo fn2(Foo f) {
  return f;
}

int main(int argc, const char * argv[]) {
  Foo a;
  Foo b;
  Foo c = a;
  Foo d(a);
  Foo e{b};

  a = b;
  a = fn();
  b = fn2(Foo());

  return 0;
}
