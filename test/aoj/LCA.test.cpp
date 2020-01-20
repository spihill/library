#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph_tree/LCA.cpp"
#include "../../template/UnWeightedGraph.cpp"
#include "../../template/WeightedGraph.cpp"


vector<int> solve1(int V, const vector<vector<int>>& g, vector<int>& A, vector<int>& B) {
	vector<int> res;
	auto L = make_lca(V);
	for (int i = 0; i < V; i++) {
		for (auto x : g[i]) {
			L.add_edge(i, x);
			L.add_edge(x, i);
		}
	}
	L.build();
	for (size_t i = 0; i < A.size(); i++) {
		res.push_back(L.lca(A[i], B[i]));
	}
	return res;
}

vector<int> solve2(int V, const vector<vector<int>>& g, vector<int>& A, vector<int>& B) {
	vector<int> res;
	auto G = make_unweighted_graph(V);
	for (int i = 0; i < V; i++) {
		for (auto x : g[i]) {
			G.add_edge(i, x);
			G.add_edge(x, i);
		}
	}
	auto L = make_lca(G);
	L.build(0);
	for (size_t i = 0; i < A.size(); i++) {
		res.push_back(L.lca(A[i], B[i]));
	}
	return res;
}

vector<int> solve3(int V, const vector<vector<int>>& g, vector<int>& A, vector<int>& B) {
	vector<int> res;
	auto G = make_weighted_graph(V);
	for (int i = 0; i < V; i++) {
		for (auto x : g[i]) {
			G.add_edge(i, x, 1);
			G.add_edge(x, i, 1);
		}
	}
	auto L = make_lca(G);
	L.build(0);
	for (size_t i = 0; i < A.size(); i++) {
		res.push_back(L.lca(A[i], B[i]));
	}
	return res;
}

int main() {
	int V; cin >> V;
	vector<vector<int>> g(V);
	for (int i = 0; i < V; i++) {
		int k;
		cin >> k;
		for (int j = 0; j < k; j++) {
			int v;
			cin >> v;
			g[i].push_back(v);
		}
	}
	int Q; cin >> Q;
	vector<int> A, B;
	for (int i = 0; i < Q; i++) {
		int u, v; cin >> u >> v;
		A.push_back(u);
		B.push_back(v);
	}
	auto r1 = solve1(V, g, A, B);
	auto r2 = solve2(V, g, A, B);
	auto r3 = solve3(V, g, A, B);
	assert(r1 == r2);
	assert(r1 == r3);
	for (auto x : r2) {
		cout << x << endl;
	}
}