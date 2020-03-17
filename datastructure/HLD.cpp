namespace hld_n {
#include "../template/WeightedVertexGraph.cpp"
#include "../datastructure/SegmentTree/SegmentTree.cpp"
using u32 = uint_fast32_t;

template<class Node, class node_type = typename Node::monoid_type>
struct HLDSegmentTree {
	SegmentTree<Node> seg;
	const vector<u32> in;
	const vector<u32> out;
	const vector<u32> nxt;
	const vector<u32> par;
	const vector<u32>& id;
	HLDSegmentTree(vector<node_type>& v, vector<u32>& in, vector<u32>& out, vector<u32>& nxt, vector<u32>& par) : seg(v), in(in), out(out), nxt(nxt), par(par), id(in) {}
	node_type get(u32 l, u32 r) const {
		return seg.get(id[l], id[r]);
	}
	void set(u32 p, node_type v) {
		return seg.set(id[p], v);
	}
	const node_type& operator[](u32 i) const {
		return seg[id[i]];
	}
	node_type subtree_sum(u32 v) const {
		return seg.get(in[v], out[v]);
	}
	node_type path_sum(u32 u, u32 v) {
		Node res;
		for (;;) {
			if (id[u] > id[v]) swap(u, v);
			res = Node::merge(res, seg.get(max(id[nxt[v]], id[u]), id[v] + 1));
			if (nxt[u] == nxt[v]) break;
			v = par[nxt[v]];
		}
		return res.val;
	}
};

template<class Node, class node_type = typename Node::monoid_type>
struct HLDecomposition : WeightedVertexGraph<node_type> {
	using WeightedVertexGraph<node_type>::n;
	using WeightedVertexGraph<node_type>::e;
	using WeightedVertexGraph<node_type>::v;
	vector<u32> sz;
	vector<u32> in;
	vector<u32> out;
	vector<u32> nxt;
	vector<u32> par;
	vector<u32>& id;
	HLDecomposition(u32 N) : WeightedVertexGraph<node_type>(N), sz(N), in(N), out(N), nxt(N), par(N, N), id(in) {}
	HLDSegmentTree<Node> make_segmenttree(u32 root = 0) {
		dfs_sz(root, n);
		u32 t = 0;
		nxt[root] = root;
		dfs_hld(root, t, n);
		vector<node_type> res(n);
		for (u32 i = 0; i < n; i++) {
			res[id[i]] = v[i].val;
		}
		return HLDSegmentTree<Node>(res, in, out, nxt, par);
	}
	node_type& operator[](u32 i) {
		return v[i].val;
	}
private:
	void dfs_sz(u32 root, u32 p) {
		sz[root] = 1;
		for (auto& u: e[root]) {
			if (u.to == p) continue;
			par[u.to] = root;
			dfs_sz(u.to, root);
			sz[root] += sz[u.to];
			if (sz[u.to] > sz[e[root][0].to]) {
				swap(u.to, e[root][0].to);
			}
		}
	}
	void dfs_hld(u32 root, u32& t, u32 p) {
		in[root] = t++;
		for (auto& u: e[root]) {
			if (u.to == p) continue;
			nxt[u.to] = (u.to == e[root][0].to ? nxt[root] : u.to);
			dfs_hld(u.to, t, root);
		}
		out[root] = t;
	}
};
template<class Node>
HLDecomposition<Node> make_hld_graph(u32 N) {
	return HLDecomposition<Node>(N);
}
}
using hld_n::HLDecomposition;
using hld_n::make_hld_graph;