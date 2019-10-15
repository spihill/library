#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_B&lang=jp"
#define MULTIPLE_SOLUTIONS

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
	for (auto& x : res.second) cout << x << endl;

	assert((int) res.second.size() == V);
	assert(1 <= V && V <= 10000);
	assert(0 <= E && E <= 100000);
	assert(res.first);
	vector<int> idx(V);
	for (int i = 0; i < V; i++) {
		idx.at(res.second.at(i)) = i;
	}
	for (int i = 0; i < V; i++) {
		for (auto& x: e.at(i)) {
			assert(idx.at(i) < idx.at(x.to));
		}
	}
	sort(res.second.begin(), res.second.end());
	res.second.erase(unique(res.second.begin(), res.second.end()), res.second.end());
	assert((int)res.second.size() == V);
	for (int i = 0; i < V; i++) {
		assert(i == res.second.at(i));
	}
}