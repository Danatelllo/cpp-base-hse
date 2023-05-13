#include "cow_string.h"
CowString::CowString(const std::string& str) {
    state_ = new State(str);
    state_->ref_count = 1;
}
CowString::~CowString() {
    if (state_->ref_count <= 1) {
        if (state_ != nullptr) {
            delete state_;
        }
    } else {
        --state_->ref_count;
    }
}
CowString::CowString(const CowString& other) {
    state_ = other.state_;
    ++state_->ref_count;
}
CowString& CowString::operator=(const CowString& other) {
    delete state_;
    state_ = other.state_;
    ++state_->ref_count;
    return (*this);
}
const char* CowString::GetData() const {
    return state_->str.data();
}
CowString& CowString::operator+=(const std::string& row) {
    if (row.empty()) {
        return *this;
    }
    if (state_->ref_count == 1) {
        state_->str += row;
    } else {
        --state_->ref_count;
        state_ = new State(state_->str);
        state_->str += row;
    }
    return *this;
}
void CowString::operator+=(const CowString row) {
    *this += row.state_->str;
}
CowString CowString::operator+(const CowString row) {
    CowString cow_str = CowString(row.state_->str + state_->str);
    return cow_str;
}
CowString CowString::operator+(const std::string& row) {
    CowString cow_str;
    cow_str.state_ = new State(row + state_->str);
    return cow_str;
}
bool CowString::operator==(const std::string& row) const {
    return state_->str == row;
}
bool CowString::operator==(const CowString row) const {
    return state_->str == row.state_->str;
}
bool CowString::operator!=(const std::string& row) const {
    return row != state_->str;
}
bool CowString::operator!=(const CowString row) const {
    return row.state_->str != state_->str;
}
const char CowString::At(size_t n) const {
    return this->state_->str[n];
}
CowString::CowString(CowString&& other) {
    state_ = other.state_;
    other.state_ = nullptr;
}
CowString::Iter CowString::operator[](size_t n) {
    return Iter(*this, n);
}
CowString::Iter CowString::begin() {
    return Iter(*this, 0);
}
CowString::ConstIter CowString::begin() const {
    return ConstIter(*this, 0);
}
CowString::Iter CowString::end() {
    return Iter(*this, this->state_->str.size());
}
CowString::ConstIter CowString::end() const {
    return ConstIter(*this, this->state_->str.size());
}

CowString CowString::Iter::operator=(char sym) {
    if (ptr_.state_->ref_count == 1) {
        ptr_.state_->str[index] = sym;
        return this->ptr_;
    }
    if (ptr_.state_->str[index] != sym) {
        --ptr_.state_->ref_count;
        std::string s = ptr_.state_->str;
        s[index] = sym;
        ptr_.state_ = new State(s);
    }
    return this->ptr_;
}
CowString::Iter CowString::Iter::operator*() {
    return *this;
}
CowString::Iter& CowString::Iter::operator++() {
    ++this->index;
    return *this;
}
bool CowString::Iter::operator==(const Iter& other) const {
    return this->ptr_.state_ == other.ptr_.state_ && this->index == other.index;
}
bool CowString::Iter::operator==(const char& sym) const {
    return this->ptr_.state_->str[index] == sym;
}
char& CowString::ConstIter::operator*() {
    return this->ptr_.state_->str[this->index];
}
CowString::ConstIter& CowString::ConstIter::operator++() {
    ++this->index;
    return *this;
}
bool CowString::ConstIter::operator==(const CowString::ConstIter& other) const {
    return this->ptr_.state_ == other.ptr_.state_ && this->index == other.index;
}
