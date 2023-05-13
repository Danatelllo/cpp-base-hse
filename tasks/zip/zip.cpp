#include "zip.h"
ZippedIter& ZippedIter::operator++() {
    ++this->first_obj;
    ++this->second_obj;
    return *this;
}
ZippedPair ZippedIter::operator*() const {
    return {*first_obj, *second_obj};
}
bool operator!=(const ZippedIter& iter, const ZippedIter& iter2) {
    return iter.second_obj != iter2.second_obj && iter.first_obj != iter2.first_obj;
}
Zipped Zip(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end) {
    Zipped iter;
    iter.iter_begin.first_obj = a_begin;
    iter.iter_begin.second_obj = b_begin;
    iter.iter_end.first_obj = a_end;
    iter.iter_end.second_obj = b_end;
    return iter;
}
ZippedIter Zipped::end() const {
    return this->iter_end;
}
ZippedIter Zipped::begin() const {
    return this->iter_begin;
}