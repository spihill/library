#define PROBLEM "https://judge.yosupo.jp/problem/scc"
#include<bits/stdc++.h>
using namespace std;

#include "../../graph/SCC.cpp"

int main() {
	int N, M; cin >> N >> M;
	auto scc = make_graph(N);
	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		scc.add_edge(a, b);
	}
	auto res = scc.build();
	cout << res.size() << endl;
	vector<vector<int>> v(res.size());
	for (int i = 0; i < N; i++) {
		v[scc[i]].push_back(i);
	}
	for (size_t i = 0; i < v.size(); i++) {
		cout << v[i].size();
		for (auto x : v[i]) cout << ' ' << x;
		cout << endl;
	}
}