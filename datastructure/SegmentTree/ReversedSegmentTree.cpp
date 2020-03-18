namespace reversed_segmenttree_n {
#include "SegmentTree.cpp"
template<class Node>
struct ReversedSegmentTree {
	using node_type = typename Node::monoid_type;
	using u32 = uint_fast32_t;
	SegmentTree<Node> seg;
	u32 sz;
	ReversedSegmentTree(vector<node_type>& v) : seg(vector<node_type>(v.rbegin(), v.rend())), sz(v.size()) {}
	void set(u32 i, Node v) {
		seg.set(sz - i - 1, v);
	}
	node_type get(u32 l, u32 r) const {
		assert(l <= r);
		return seg.get(sz - r, sz - l);
	}
	const node_type& operator[](u32 i) const {
		return seg[sz - i - 1];
	}
};
}
using reversed_segmenttree_n::ReversedSegmentTree;