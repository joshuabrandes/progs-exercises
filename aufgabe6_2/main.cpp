#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {

    std::shared_ptr<int> s1(new int(2));
    std::shared_ptr<int> s2;
    std::unique_ptr<int> u1(new int(3));
    std::weak_ptr<int>   w1;

    {
        std::shared_ptr<int> s4(s1);
        s2 = s4;
        std::unique_ptr<int> u2(std::move(u1));
        std::shared_ptr<int> s5(new int(5));
        w1 = s5;
        /**/
    }

    s1.reset();
    std::shared_ptr<int> s6 = w1.lock();

    std::cout << (s1 != nullptr ? *s1 : 0) << std::endl; // 0
    std::cout << (s2 != nullptr ? *s2 : 0) << std::endl; // 2
    std::cout << (u1 != nullptr ? *u1 : 0) << std::endl; // 3
    std::cout << (s6 != nullptr ? *s6 : 0) << std::endl; // 5
    return 0;
}