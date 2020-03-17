#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
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
		int p; cin >> p;
		G.add_edge(p, i);
	}
	auto seg = G.make_segmenttree(0);
	for (int i = 0; i < Q; i++) {
		int q; cin >> q;
		if (q == 0) {
			int u, x; cin >> u >> x;
			seg.set(u, seg[u] + x);
		} else {
			int u; cin >> u;
			cout << seg.subtree_sum(u) << endl;
		}
	}
	return 0;
}