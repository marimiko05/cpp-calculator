#pragma once

#include <string>
#include <optional>
#include <cmath>
#include <type_traits>
#include <sstream>
#include "rational.h"
#include "pow.h"

using Error = std::string;

template <typename Number>
class Calculator {
public:
    Calculator() : result_(Number{}), has_mem_(false) {}

    void Set(Number n) {
        result_ = n;
    }

    Number GetNumber() const {
        return result_;
    }

    std::optional<Error> Add(Number n) {
        result_ += n;
        return std::nullopt;
    }

    std::optional<Error> Sub(Number n) {
        result_ -= n;
        return std::nullopt;
    }

    std::optional<Error> Mul(Number n) {
        result_ *= n;
        return std::nullopt;
    }

    std::optional<Error> Div(Number n) {
        if constexpr (std::is_floating_point_v<Number>) {
            result_ /= n;
            return std::nullopt;
        } else if constexpr (std::is_integral_v<Number> || std::is_same_v<Number, Rational>) {
            if (n == Number{0}) {
                return "Division by zero";
            }
            result_ /= n;
            return std::nullopt;
        }
        return std::nullopt;
    }

    std::optional<Error> Pow(Number n) {
        if (result_ == Number{0} && n == Number{0}) {
            return "Zero power to zero";
        }

        if constexpr (std::is_floating_point_v<Number>) {
            result_ = std::pow(result_, n);
            return std::nullopt;
        } else if constexpr (std::is_integral_v<Number>) {
            if (n < 0) {
                return "Integer negative power";
            }
            result_ = ::IntegerPow(result_, n);
            return std::nullopt;
        } else if constexpr (std::is_same_v<Number, Rational>) {
            if (n.GetDenominator() != 1) {
                return "Fractional power is not supported";
            }
            result_ = ::Pow(result_, n);
            return std::nullopt;
        }
        return std::nullopt;
    }

    void Save() {
        mem_ = result_;
        has_mem_ = true;
    }

    void Load() {
        if (has_mem_) {
            result_ = mem_;
        }
    }

    bool GetHasMem() const {
        return has_mem_;
    }

    std::string GetNumberRepr() const {
        std::ostringstream oss;
        if constexpr (std::is_same_v<Number, uint8_t>) {
            oss << static_cast<int>(result_);
        } else {
            oss << result_;
        }
        return oss.str();
    }

private:
    Number result_;
    Number mem_ = Number{};
    bool has_mem_ = false;
};
