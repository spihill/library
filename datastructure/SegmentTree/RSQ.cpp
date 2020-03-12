namespace RSQ_n {
#include "SegmentTree.cpp"
#include "../../monoid/plus_monoid.cpp"
template<class T> using RSQ = SegmentTree<plus_monoid<T>>;
}
using RSQ_n::RSQ;