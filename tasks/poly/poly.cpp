#include "poly.h"
Poly::Poly(const std::vector<int64_t> value) {
    size_t deg = 0;
    for (size_t j = 0; j < value.size(); ++j) {
        if (value[j] != 0) {
            polynomial_[deg] = value[j];
        }
        ++deg;
    }
}

Poly::Poly(const std::vector<std::pair<int64_t, int64_t>> value) {
    for (auto& deg_value : value) {
        polynomial_[deg_value.first] = deg_value.second;
    }
}

int64_t Poly::operator()(int64_t number) const {
    int64_t answer = 0;
    for (const auto& [power, coeff] : polynomial_) {
        int64_t t = 1;
        int64_t i = 0;
        while (i < power) {
            t *= number;
            i += 1;
        }
        answer += coeff * t;
    }
    return answer;
}

bool Poly::operator!=(const Poly& g) const {
    for (const auto& deg_value : polynomial_) {
        if (polynomial_.size() != g.polynomial_.size()) {
            return false;
        } else {
            auto it = g.polynomial_.find(deg_value.first);
            if (it == g.polynomial_.end() || deg_value.second != it->second) {
                return false;
            }
        }
    }
    return true;
}

bool Poly::operator==(const Poly& g) const {
    for (const auto& deg_value : polynomial_) {
        if (polynomial_.size() != g.polynomial_.size()) {
            return false;
        } else {
            auto it = g.polynomial_.find(deg_value.first);
            if (it == g.polynomial_.end() || deg_value.second != it->second) {
                return false;
            }
        }
    }
    return true;
}

Poly Poly::operator+(const Poly& f) {
    Poly result_sum = f;
    for (const auto& deg_value : polynomial_) {
        result_sum.polynomial_[deg_value.first] += deg_value.second;
    }
    return result_sum;
}

Poly Poly::operator-(const Poly& f) {
    Poly result_sum = *this;
    for (const auto& deg_value : f.polynomial_) {
        result_sum.polynomial_[deg_value.first] -= deg_value.second;
    }
    return result_sum;
}

Poly Poly::operator+=(const Poly& f) {
    *this = *this + f;
    return *this;
}

Poly Poly::operator-=(const Poly& f) {
    *this = *this - f;
    return *this;
}

Poly Poly::operator-() const {
    Poly empty_poly;
    return empty_poly -= *this;
}

Poly Poly::operator*(const Poly& f) {
    Poly answer;
    for (auto& deg_value : polynomial_) {
        Poly result_one_malt;
        for (auto& multiplier : f.polynomial_) {
            result_one_malt.polynomial_[multiplier.first + deg_value.first] += multiplier.second * deg_value.second;
        }
        answer += result_one_malt;
    }
    return answer;
}

std::ostream& operator<<(std::ostream& stream, const Poly& g) {
    stream << "y = ";
    if (!g.polynomial_.empty()) {
        for (auto itr = g.polynomial_.rbegin(); itr != g.polynomial_.rend(); ++itr) {
            if (itr->first > 1) {
                stream << itr->second << "x"
                       << "^" << std::to_string(itr->first) << " + ";
            } else if (itr->first == 1) {
                stream << itr->second << "x"
                       << " + ";
            } else {
                stream << itr->second;
            }
        }
    } else {
        stream << "0";
    }
    return stream;
}
