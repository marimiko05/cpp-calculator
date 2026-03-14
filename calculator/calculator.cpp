#include <cmath>
#include "calculator.h"
#include <string>

void Calculator::Set(Number n){

    result_ = n;
    zero_div_ = false;
};

Number Calculator::GetNumber() const{

    return result_;
};

void Calculator::Add(Number n){

    result_ += n;
};

void Calculator::Sub(Number n){

    result_ -= n;
};

void Calculator::Div(Number n){

    if (n != 0) {
        result_ /= n;
    } else {
        zero_div_ = true;
    }

};

void Calculator::Mul(Number n){

    result_ *= n;
};

void Calculator::Pow(Number n){

    result_ = std::pow(result_, n);
};

std::string Calculator::GetNumberRepr() const{

    if (zero_div_) {
        return "inf";
    }
    std::string numst = std::to_string(result_);
    return numst;
}
