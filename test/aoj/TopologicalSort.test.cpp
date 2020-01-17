#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/4/GRL_4_B"
#include<bits/stdc++.h>

using namespace std;

#include "../../graph/TopologicalSort.cpp"

int main() {
	int V, E; cin >> V >> E;
	graph e(V);
	for (int i = 0; i < E; i++) {
		int v, u; cin >> v >> u;
		e[v].emplace_back(u);
	}
	auto res = TopologicalSort(e);
	for (auto& x : res) cout << x << endl;

	assert((int) res.size() == V);
	assert(1 <= V && V <= 10000);
	assert(0 <= E && E <= 100000);
	vector<int> idx(V);
	for (int i = 0; i < V; i++) {
		idx.at(res.at(i)) = i;
	}
	for (int i = 0; i < V; i++) {
		for (auto& x: e.at(i)) {
			assert(idx.at(i) < idx.at(x.to));
		}
	}
	sort(res.begin(), res.end());
	res.erase(unique(res.begin(), res.end()), res.end());
	assert((int)res.size() == V);
	for (int i = 0; i < V; i++) {
		assert(i == res.at(i));
	}
}