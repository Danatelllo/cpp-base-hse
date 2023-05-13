#pragma once

#include <forward_list>
#include <string>

using Value = std::string;
using Iterator = std::forward_list<std::string>::const_iterator;
using ZippedPair = std::pair<const Value&, const Value&>;

class ZippedIter {
public:
    Iterator first_obj;
    Iterator second_obj;
    ZippedPair operator*() const;
    ZippedIter& operator++();
};
class Zipped {
public:
    ZippedIter iter_begin;
    ZippedIter iter_end;
    ZippedIter begin() const;
    ZippedIter end() const;
};
Zipped Zip(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end);
bool operator!=(ZippedIter const& iter1, ZippedIter const& iter2);