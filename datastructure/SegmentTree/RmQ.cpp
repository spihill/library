namespace RmQ_n {
#include "SegmentTree.cpp"
#include "../../monoid/min_monoid.cpp"
template<class T> using RmQ = SegmentTree<min_monoid<T>>;
}
using RmQ_n::RmQ;