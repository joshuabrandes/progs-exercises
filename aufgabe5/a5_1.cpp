
#include <iostream>

class Integer {
public:
    Integer(int i) {
        i_ = new int(i);
    }

    // löst das Problem, dass Platz für i_ reserviert, aber nicht freigegeben bei Zuweisung
    Integer operator=(const Integer &rhs) {
        if (this != &rhs) {
            return *this;
        }
        delete i_;
        i_ = new int(*(rhs.i_));
        return *this;
    }

    ~Integer() {
        delete i_;
    }

    int get_integer() const { return *i_; }

private:
    int *i_;
};

auto getAdder(int x) {
    Integer i(x);
    return [i](int y) { return i.get_integer() + y; };
}

int main() {

    auto x = 2;
    auto f = getAdder(2);

    std::cout << f(x) << std::endl;

    return 0;
}
