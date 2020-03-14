#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"
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
		int u, v; cin >> u >> v;
		G.add_edge(u, v);
		G.add_edge(v, u);
	}
	RSQ<long long> rsq(G.build(0));
	for (int i = 0; i < Q; i++) {
		int q; cin >> q;
		if (q == 0) {
			int u, x; cin >> u >> x;
			rsq.set(G.id[u], rsq[G.id[u]] + x);
		} else {
			int u, v; cin >> u >> v;
			auto t = G.path(u, v);
			long long sum = 0;
			for (auto p : t) {
				sum += rsq.get(p.first, p.second);
			}
			cout << sum << endl;
		}
	}
	return 0;
}