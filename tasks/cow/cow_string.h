#pragma once
#include <iostream>
#include <string_view>
#include <cstring>
#include <utility>
#include <algorithm>
struct State {
    int ref_count = 1;
    std::string str;
    State(std::string row) : str(row){};
};
class CowString {
public:
    CowString(){};
    CowString(const std::string& str);
    ~CowString();
    CowString(const CowString& other);
    CowString(CowString&& other);
    CowString& operator=(const CowString& other);
    const char* GetData() const;
    CowString& operator+=(const std::string& row);
    void operator+=(const CowString row);
    CowString operator+(const CowString row);
    CowString operator+(const std::string& row);
    bool operator==(const std::string& row) const;
    bool operator==(const CowString row) const;
    bool operator!=(const std::string& row) const;
    bool operator!=(const CowString row) const;
    const char At(size_t n) const;
    class Iter {
    public:
        CowString& ptr_;
        size_t index;
        Iter(CowString& ptr, size_t n) : ptr_(ptr), index(n){};
        CowString operator=(char sym);
        Iter operator*();
        Iter& operator++();
        bool operator==(const Iter& other) const;
        bool operator==(const char& sym) const;
    };
    class ConstIter {
    public:
        const CowString& ptr_;
        size_t index;
        ConstIter(const CowString& ptr, size_t n) : ptr_(ptr), index(n){};
        char& operator*();
        ConstIter& operator++();
        bool operator==(const ConstIter& other) const;
    };
    Iter operator[](size_t n);
    Iter begin();
    Iter end();
    ConstIter begin() const;
    ConstIter end() const;
    State* state_;
};