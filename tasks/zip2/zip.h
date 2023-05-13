#pragma once
#include <vector>

#include <forward_list>
#include <string>
#include <iterator>
template <typename Iter1, typename Iter2>
class ZippedIter {
public:
    ZippedIter() {};
    explicit ZippedIter(Iter1 a, Iter2 b) {
        iter_a_ = a;
        iter_b_ = b;
    }
    ZippedIter& operator++() {
        ++iter_a_;
        ++iter_b_;
        return *this;
    }
    auto operator*() const {
        return std::pair{*iter_a_, *iter_b_};
    }
    bool operator!=(const ZippedIter& iter2) {
        return this->iter_a_ != iter2.iter_a_ && this->iter_b_ != iter2.iter_b_;
    }

private:
    Iter1 iter_a_;
    Iter2 iter_b_;
};

template <typename Iter1, typename Iter2>
class Zipped {
public:
    Zipped() {};
     Zipped(Iter1 a_begin, Iter1 a_end, Iter2 b_begin, Iter2 b_end) {
        begin_ = ZippedIter(a_begin, b_begin);
        end_ = ZippedIter(a_end, b_end);
    }
    auto begin() const {
        return begin_;
    }
    auto end() const {
        return end_;
    }

private:
    ZippedIter<Iter1, Iter2> begin_;
    ZippedIter<Iter1, Iter2> end_;
};

template <typename Sequence1, typename Sequence2>
auto Zip(const Sequence1& sequence1, const Sequence2& sequence2) {
    Zipped iter = Zipped(std::begin(sequence1), std::end(sequence1), std::begin(sequence2), std::end(sequence2));
    return iter;
}
