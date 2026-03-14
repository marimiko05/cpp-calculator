#pragma once

#include <string>

using Number = double;

class Calculator {
public:

    void Set(Number n);
    Number GetNumber() const;
    void Add(Number n);
    void Sub(Number n);
    void Div(Number n);
    void Mul(Number n);
    void Pow(Number n);
    std::string GetNumberRepr() const;

private:

    Number result_ = 0;
    bool zero_div_ = false;
};

