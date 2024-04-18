#include <iostream>
#include <vector>
#include <string>

/**
 * Scanner function
 * @param input_tokens
 * Regeln:
 * integer  -> digit digit*
 * digit    -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 (T)
 * id       -> letter letter*
 * letter   -> a | b | c ... | z | A | B | ... | Z (T)
 * add_op  → + | - (T)
 * mult_op → * | / (T)
 */
void scanner(std::vector<std::string> &input_tokens) {
    std::string total_input;
    total_input = "";
    // read input_tokens into total_input
    for (int i = 0; i < input_tokens.size(); i++) {
        total_input += input_tokens[i];
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
