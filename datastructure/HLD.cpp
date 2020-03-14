namespace hld_n {
#include "../template/WeightedVertexGraph.cpp"
using weighted_vertex_graph_n::WeightedVertexGraph;
using weighted_vertex_graph_n::make_weighted_vertex_graph;
using u32 = uint_fast32_t;
template<class T>
struct HLDecomposition : WeightedVertexGraph<T> {
	using WeightedVertexGraph<T>::n;
	using WeightedVertexGraph<T>::e;
	using WeightedVertexGraph<T>::v;
	vector<u32> sz;
	vector<u32> in;
	vector<u32> out;
	vector<u32> nxt;
	vector<u32> par;
	vector<u32>& id;
	HLDecomposition(u32 N) : WeightedVertexGraph<T>(N), sz(N), in(N), out(N), nxt(N), par(N, N), id(in) {}
	vector<T> build(u32 root = 0) {
		dfs_sz(root, n);
		u32 t = 0;
		nxt[root] = root;
		dfs_hld(root, t, n);
		vector<T> res(n);
		for (u32 i = 0; i < n; i++) {
			res[id[i]] = v[i].val;
		}
		return res;
	}
	pair<u32, u32> subtree(u32 v) {
		return {in[v], out[v]};
	}
	vector<pair<u32, u32>> path(u32 u, u32 v) {
		vector<pair<u32, u32>> res;
		for (;;) {
			if (id[u] > id[v]) swap(u, v);
			res.emplace_back(max(id[nxt[v]], id[u]), id[v] + 1);
			if (nxt[u] == nxt[v]) break;
			v = par[nxt[v]];
		}
		reverse(res.begin(), res.end());
		return res;
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
template<class T = long long>
HLDecomposition<T> make_hld_graph(u32 N) {
	return HLDecomposition<T>(N);
}
}
using hld_n::HLDecomposition;
using hld_n::make_hld_graph;