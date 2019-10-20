#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph_tree/LCA.cpp"

int main() {
	int V;
	cin >> V;
	graph L(V);
	for (int i = 0; i < V; i++) {
		int k;
		cin >> k;
		for (int j = 0; j < k; j++) {
			int v;
			cin >> v;
			L.add_edge(i, v);
			L.add_edge(v, i);
		}
	}
	L.build(0);
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int u, v;
		cin >> u >> v;
		cout << L.lca(u, v) << endl;
	}
}