#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph/Bellmanford.cpp"

int main() {
	int V, E, S;
	cin >> V >> E >> S;
	graph<int> B(V);
	for (int i = 0; i < E; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		B.add_edge(a, b, c);
	}
	Bellmanford(B, S, INT_MAX);
	for (int i = 0; i < V; i++) {
		if (!B.valid[i] && B.dist[i] != INT_MAX) {
			cout << "NEGATIVE CYCLE" << endl;
			return 0;
		}
	}
	for (int i = 0; i < V; i++) {
		if (!B.valid[i]) cout << "INF" << endl;
		else cout << B.dist[i] << endl;
	}
}