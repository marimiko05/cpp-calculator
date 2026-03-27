#pragma once

#include <numeric>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cstdint>

class Rational {
public:

    Rational() = default;
    Rational(int numerator) : numerator_(numerator) {}
    Rational(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {
        if (denominator_ == 0) {
            std::abort();
        }
        Reduction();
    }

    int GetNumerator() const { return numerator_; }
    int GetDenominator() const { return denominator_; }

    Rational Inv() const {
        return Rational(denominator_, numerator_);
    }

    Rational& operator+=(const Rational& other) {
        numerator_ = numerator_ * other.denominator_ + other.numerator_ * denominator_;
        denominator_ = denominator_ * other.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator-=(const Rational& other) {
        numerator_ = numerator_ * other.denominator_ - other.numerator_ * denominator_;
        denominator_ = denominator_ * other.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator*=(const Rational& other) {
        numerator_ *= other.numerator_;
        denominator_ *= other.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator/=(const Rational& other) {
        numerator_ *= other.denominator_;
        denominator_ *= other.numerator_;
        Reduction();
        return *this;
    }

    Rational& operator=(const Rational&) = default;
    Rational operator+() const { return *this; }
    Rational operator-() const { return Rational(-numerator_, denominator_); }

    explicit operator double() const {
        return static_cast<double>(numerator_) / denominator_;
    }

    friend std::istream& operator>>(std::istream&, Rational&);
    friend std::ostream& operator<<(std::ostream&, const Rational&);
    friend bool operator==(const Rational&, const Rational&);
    friend bool operator<(const Rational&, const Rational&);

private:
    int numerator_ = 0;
    int denominator_ = 1;

    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }
};

inline Rational operator+(Rational lhs, const Rational& rhs) {
    lhs += rhs;
    return lhs;
}

inline Rational operator-(Rational lhs, const Rational& rhs) {
    lhs -= rhs;
    return lhs;
}

inline Rational operator*(Rational lhs, const Rational& rhs) {
    lhs *= rhs;
    return lhs;
}

inline Rational operator/(Rational lhs, const Rational& rhs) {
    lhs /= rhs;
    return lhs;
}

inline bool operator==(const Rational& lhs, const Rational& rhs) {
    return static_cast<std::int64_t>(lhs.GetNumerator()) * rhs.GetDenominator() ==
           static_cast<std::int64_t>(rhs.GetNumerator()) * lhs.GetDenominator();
}

inline bool operator<(const Rational& lhs, const Rational& rhs) {
    return static_cast<std::int64_t>(lhs.GetNumerator()) * rhs.GetDenominator() <
           static_cast<std::int64_t>(rhs.GetNumerator()) * lhs.GetDenominator();
}

inline bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

inline bool operator>(const Rational& lhs, const Rational& rhs) {
    return rhs < lhs;
}

inline bool operator<=(const Rational& lhs, const Rational& rhs) {
    return !(rhs < lhs);
}

inline bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs);
}

inline std::istream& operator>>(std::istream& is, Rational& r) {
    int n, d;
    char slash;

    if (!(is >> n)) {
        return is;
    }

    if (is >> std::ws >> slash) {
        if (slash == '/') {
            if (!(is >> d) || d == 0) {
                is.setstate(std::ios::failbit);
                return is;
            }
            r = Rational(n, d);
        } else {
            is.unget();
            r = Rational(n, 1);
        }
    } else {
        is.clear();
        r = Rational(n, 1);
    }
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const Rational& r) {
    if (r.denominator_ == 1) {
        os << r.numerator_;
    } else {
        os << r.numerator_ << " / " << r.denominator_;
    }
    return os;
}
