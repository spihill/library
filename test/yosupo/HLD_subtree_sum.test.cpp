#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#include<bits/stdc++.h>
using namespace std;

#include "../../datastructure/HLD.cpp"
#include "../../datastructure/SegmentTree/RSQ.cpp"

int main() {
	int N, Q; cin >> N >> Q;
	auto G = make_hld_graph(N);
	for (int i = 0; i < N; i++) {
		int a; cin >> a;
		G.v[i].val = a;
	}
	for (int i = 1; i < N; i++) {
		int p; cin >> p;
		G.add_edge(p, i);
	}
	RSQ<long long> rsq(G.build(0));
	for (int i = 0; i < Q; i++) {
		int q; cin >> q;
		if (q == 0) {
			int u, x; cin >> u >> x;
			rsq.set(G.id[u], rsq[G.id[u]] + x);
		} else {
			int u; cin >> u;
			auto t = G.subtree(u);
			cout << rsq.get(t.first, t.second) << endl;
		}
	}
	return 0;
}