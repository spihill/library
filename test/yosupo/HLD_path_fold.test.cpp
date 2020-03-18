#define PROBLEM "https://judge.yosupo.jp/problem/vertex_set_path_composite"
#include<bits/stdc++.h>
using namespace std;

#include "../../datastructure/HLD.cpp"
#include "../../monoid/affine_monoid.cpp"
#include "../../math/ModInt.cpp"
using modint = ModInt<998244353>;

int main() {
	int N, Q; cin >> N >> Q;
	auto G = make_hld_graph<affine_monoid<modint>>(N);
	for (int i = 0; i < N; i++) {
		cin >> G[i].first >> G[i].second;
	}
	for (int i = 1; i < N; i++) {
		int u, v; cin >> u >> v;
		G.add_edge(u, v);
		G.add_edge(v, u);
	}
	auto seg = G.make_segmenttree(0);
	for (int i = 0; i < Q; i++) {
		int q; cin >> q;
		if (q == 0) {
			int p, c, d; cin >> p >> c >> d;
			seg.set(p, {c, d});
		} else {
			int u, v, x; cin >> u >> v >> x;
			auto r = seg.path_fold(u, v);
			cout << r.first * x + r.second << endl;
		}
	}
	return 0;
}