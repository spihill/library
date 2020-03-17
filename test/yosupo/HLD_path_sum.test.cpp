#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"
#include<bits/stdc++.h>
using namespace std;

#include "../../datastructure/HLD.cpp"
#include "../../monoid/plus_monoid.cpp"

int main() {
	int N, Q; cin >> N >> Q;
	auto G = make_hld_graph<plus_monoid<long long>>(N);
	for (int i = 0; i < N; i++) {
		cin >> G[i];
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
			int u, x; cin >> u >> x;
			seg.set(u, seg[u] + x);
		} else {
			int u, v; cin >> u >> v;
			cout << seg.path_sum(u, v) << endl;
		}
	}
	return 0;
}