// В этом файле определения функций.
// За основу возьмите решение предыдущей задачи.
#include <iostream>
#include <string>
#include <cmath>
#include "calculator.h"

bool ReadNumber(Number& result) {
    std::cin >> result;
    if (!std::cin) {
        std::cerr << "Error: Numeric operand expected" << std::endl;
        return false;
    } else {
        return true;
    }
}

bool ReadRightNumber(Number& right_num) {
    std::cin >> right_num;
    if (!std::cin) {
        std::cerr << "Error: Numeric operand expected" << std::endl;
        return false;
    }
    return true;
}

std::string ReadOperation() {
    std::string op;
    std::cin >> op;

    if (op == "+" || op == "*" || op == "-" || op == "/" || 
        op == ":" || op == "**" || op == "=" || op == "c" || 
        op == "q" || op == "s" || op == "l") {
        return op;
    } else {
        std::cerr << "Error: Unknown token " << op << std::endl;
        return "";
    }
}

bool RunCalculatorCycle() {
    Number saved_num;
    Number result = 0;
    bool number_is_saved = false;

    if (!ReadNumber(result)) {
        return false;
    }

    while (true) {
        std::string op = ReadOperation();
        
        if (op.empty()) {
            return false;
        }

        if (op == "=") {
            std::cout << result << std::endl;
        } else if (op == "c") {
            result = 0;
        } else if (op == "q") {
            return true;
        } else if (op == "s") {
            saved_num = result;
            number_is_saved = true;
        } else if (op == "l") {
            if (!number_is_saved) {
                std::cerr << "Error: Memory is empty" << std::endl;
                return false;
            }
            result = saved_num;
        } else {        
            Number right_num;
            if (!ReadRightNumber(right_num)) {
                return false;
            }

            if (op == "+") {
                result = result + right_num;
            } else if (op == "*") {
                result = result * right_num;
            } else if (op == "-") {
                result = result - right_num;
            } else if (op == "/") {
                result = result / right_num;
            } else if (op == ":") {
                result = right_num;
            } else if (op == "**") {
                result = std::pow(result, right_num);
            }
        }
    }
}