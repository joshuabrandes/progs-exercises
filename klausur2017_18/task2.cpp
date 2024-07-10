#include <iostream>
#include <functional>

auto Num(int a) {
    return [a] { return a; };
}

auto Plus(std::function<int()> b, std::function<int()> c) {
    return [b, c] { return b() + c(); };
}

int main() {
    auto d = 2;
    auto e = 3;
    auto f = Plus(Num(d), Plus(Num(e), Num(4)));
    std::cout << f() << std::endl;

    e = 5;
    std::cout << f() << std::endl;

    return 0;
}
