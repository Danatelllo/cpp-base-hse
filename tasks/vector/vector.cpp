#include "vector.h"
Vector::Vector(size_t size) {
    vector_ = new int[size];
    for (size_t j = 0; j < size; ++j) {
        vector_[j] = 0;
    }
    size_ = size;
    capacity_ = size;
}
Vector::Vector(std::initializer_list<ValueType> list) {
    vector_ = new int[list.size()];
    size_ = list.size();
    capacity_ = size_;
    size_t j = 0;
    for (auto& value : list) {
        vector_[j] = value;
        ++j;
    }
}
Vector::Vector(const Vector& other) {
    vector_ = new int[other.size_];
    capacity_ = other.size_;
    size_ = other.size_;
    for (size_t j = 0; j < other.size_; ++j) {
        vector_[j] = other[j];
    }
}
Vector& Vector::operator=(const Vector& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    delete[] vector_;
    vector_ = new int[other.size_];
    for (size_t j = 0; j < other.size_; ++j) {
        vector_[j] = other[j];
    }
    return *this;
}
Vector::~Vector() {
    delete[] vector_;
}
Vector::SizeType Vector::Size() const {
    return size_;
}
Vector::SizeType Vector::Capacity() const {
    return capacity_;
}
const Vector::ValueType* Vector::Data() const {
    return vector_;
}

Vector::ValueType& Vector::operator[](size_t position) {
    return vector_[position];
}
Vector::ValueType Vector::operator[](size_t position) const {
    return vector_[position];
}
bool Vector::operator==(const Vector& other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (size_t j = 0; j < other.size_; ++j) {
        if (vector_[j] != other.vector_[j]) {
            return false;
        }
    }
    return true;
}
bool Vector::operator!=(const Vector& other) const {
    return !(other == *this);
}
void Vector::PopBack() {
    vector_[size_ - 1] = 0;
    --size_;
}
void Vector::Clear() {
    for (size_t j = 0; j < size_; ++j) {
        vector_[j] = 0;
    }
    size_ = 0;
}
void Vector::Reserve(SizeType new_capacity) {
    if (capacity_ < new_capacity) {
        int* new_vector = new int[new_capacity];
        for (size_t j = 0; j < size_; ++j) {
            new_vector[j] = vector_[j];
        }
        delete[] vector_;
        vector_ = new_vector;
        capacity_ = new_capacity;
    }
}
void Vector::PushBack(const ValueType& new_element) {
    if (capacity_ == 0) {
        vector_ = new int[1];
        vector_[0] = new_element;
        capacity_ = 1;
        size_ = 1;
    } else {
        if (capacity_ == size_) {
            int* new_vector = new int[capacity_ * 2];
            for (size_t j = 0; j < size_; ++j) {
                new_vector[j] = vector_[j];
            }
            delete[] vector_;
            vector_ = new_vector;
            vector_[size_] = new_element;
            ++size_;
            capacity_ *= 2;

        } else {
            vector_[size_] = new_element;
            ++size_;
        }
    }
}
void Vector::Swap(Vector& other) {
    std::swap(other.vector_, this->vector_);
    std::swap(other.size_, this->size_);
    std::swap(other.capacity_, this->capacity_);
}
Vector::Iterator Vector::Begin() {
    Iterator it;
    it.iter_ = &vector_[0];
    return it;
}
Vector::Iterator Vector::End() {
    Iterator it;
    it.iter_ = &vector_[size_];
    return it;
}
Vector::Iterator Vector::begin() {
    Iterator it;
    it.iter_ = &vector_[0];
    return it;
}
Vector::Iterator Vector::end() {
    Iterator it;
    it.iter_ = &vector_[size_];
    return it;
}

Vector::Iterator::Iterator(ValueType* pointer) {
    iter_ = pointer;
}
Vector::ValueType& Vector::Iterator::operator*() const {
    return *iter_;
}
Vector::ValueType* Vector::Iterator::operator->() const {
    return iter_;
}
Vector::Iterator& Vector::Iterator::operator=(Vector::Iterator other) {
    iter_ = other.iter_;
    return *this;
}
Vector::Iterator& Vector::Iterator::operator++() {
    ++iter_;
    return *this;
}
Vector::Iterator Vector::Iterator::operator++(int) {
    Iterator old_iter = *this;
    ++iter_;
    return old_iter;
}
Vector::Iterator& Vector::Iterator::operator--() {
    --iter_;
    return *this;
}
Vector::Iterator Vector::Iterator::operator--(int) {
    Iterator old_iter = *this;
    --iter_;
    return old_iter;
}
Vector::Iterator Vector::Iterator::operator+(Vector::DifferenceType shift) {
    Iterator it = *this;
    it.iter_ += shift;
    return it;
}
Vector::DifferenceType Vector::Iterator::operator-(Vector::Iterator other) {
    return iter_ - other.iter_;
}
Vector::Iterator& Vector::Iterator::operator+=(Vector::DifferenceType shift) {
    iter_ += shift;
    return *this;
}
Vector::Iterator& Vector::Iterator::operator-=(Vector::DifferenceType shift) {
    iter_ -= shift;
    return *this;
}
bool Vector::Iterator::operator==(const Vector::Iterator& other) const {
    return iter_ == other.iter_;
}
bool Vector::Iterator::operator!=(const Vector::Iterator& other) const {
    return iter_ != other.iter_;
}
std::strong_ordering Vector::Iterator::operator<=>(const Vector::Iterator& other) const {
    if (iter_ == other.iter_) {
        return std::strong_ordering::equal;
    } else if (iter_ < other.iter_) {
        return std::strong_ordering::less;
    } else {
        return std::strong_ordering::greater;
    }
}
std::strong_ordering Vector::operator<=>(const Vector& other) const {
    for (size_t j = 0; j < std::min(size_, other.size_); ++j) {
        if (vector_[j] < other.vector_[j]) {
            return std::strong_ordering::less;
        } else if (vector_[j] > other.vector_[j]) {
            return std::strong_ordering::greater;
        }
    }
    if (other.size_ != size_) {
        if (size_ > other.size_) {
            return std::strong_ordering::greater;
        } else {
            return std::strong_ordering::less;
        }
    }
    return std::strong_ordering::equal;
}