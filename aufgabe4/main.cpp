#include <iostream>
#include <vector>
#include <functional>

void exercise1() {
    std::vector<std::function<void()>> arr;

    auto consoleLog = [](int j) -> void {
        std::cout << j << std::endl;
    };

    for (int i = 0; i < 10; i++) {
        int j = 0;
        arr.emplace_back([j, consoleLog]() mutable {
            j++;
            consoleLog(j);
        });
    }

    for (auto& a: arr) {
        a();
    }
}



int main() {
    exercise1();
    return 0;
}
