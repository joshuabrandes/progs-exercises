#include <iostream>
#include <string>
#include <cctype>

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
class Token {
public:
    enum Value {
        INTEGER,
        ID,
        ADD_OP,
        MULT_OP,
        UNKNOWN
    };

    explicit Token(Value value) : value(value) {}

    Value value;

    static std::string to_string(Token token) {
        switch (token.value) {
            case INTEGER:
                return "INTEGER";
            case ID:
                return "ID";
            case ADD_OP:
                return "ADD_OP";
            case MULT_OP:
                return "MULT_OP";
            case UNKNOWN:
                return "UNKNOWN";
            default:
                return "INVALID_TOKEN";
        }
    }
};

class Scanner {
public:
    explicit Scanner(const std::string& input) : input(input), pos(0) {}

    const std::string &input;
    size_t pos;

    std::pair<Token, std::string> next_token() {
        while (pos < input.size() && std::isspace(input[pos])) {
            pos++;
        }

        char currentChar = input[pos];

        if (std::isdigit(currentChar)) {
            std::string integer = scanInteger();
            return {Token(Token::INTEGER), integer};
        } else if (std::isalpha(currentChar)) {
            std::string identifier = scanIdentifier();
            return {Token(Token::ID), identifier};
        } else if (currentChar == '+' || currentChar == '-') {
            pos++;
            return {Token(Token::ADD_OP), std::string(1, currentChar)};
        } else if (currentChar == '*' || currentChar == '/') {
            pos++;
            return {Token(Token::MULT_OP), std::string(1, currentChar)};
        } else {
            pos++;
            return {Token(Token::UNKNOWN), std::string(1, currentChar)};
        }
    }

private:
    std::string scanInteger() {
        std::string integer;
        while (pos < input.size() && std::isdigit(input[pos])) {
            integer += input[pos];
            pos++;
        }
        return integer;
    }

    std::string scanIdentifier() {
        std::string identifier;
        while (pos < input.size() && std::isalpha(input[pos])) {
            identifier += input[pos];
            pos++;
        }
        return identifier;
    }
};

int main() {
    std::string input = "42 + abc / 2";
    Scanner scanner(input);

    while (scanner.pos < scanner.input.size()) {
        auto token = scanner.next_token();
        std::cout << "Token Type: " << Token::to_string(token.first)
                  << ", Value: " << token.second << std::endl;
    }

    return 0;
}
