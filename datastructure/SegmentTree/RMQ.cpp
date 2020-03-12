namespace RMQ_n {
#include "SegmentTree.cpp"
#include "../../monoid/max_monoid.cpp"
template<class T> using RMQ = SegmentTree<max_monoid<T>>;
}
using RMQ_n::RMQ;