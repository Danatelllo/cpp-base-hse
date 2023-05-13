
#pragma once
#include <vector>
#include <map>
#include <math.h>
#include <iostream>
class Poly {
public:
    Poly(){};
    explicit Poly(const std::vector<int64_t> value);
    explicit Poly(const std::vector<std::pair<int64_t, int64_t>> value);
    int64_t operator()(int64_t number) const;
    bool operator!=(const Poly& g) const;
    bool operator==(const Poly& g) const;
    Poly operator+(const Poly& f);
    Poly operator-(const Poly& f);
    Poly operator+=(const Poly& f);
    Poly operator-=(const Poly& f);
    Poly operator-() const;
    Poly operator*(const Poly& f);
    friend std::ostream& operator<<(std::ostream& stream, const Poly& g);

private:
    std::map<int64_t, int64_t> polynomial_;
};