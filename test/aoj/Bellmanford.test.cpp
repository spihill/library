#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph/Bellmanford.cpp"

int main() {
	int V, E, S;
	cin >> V >> E >> S;
	Bellmanford<int> B(V);
	for (int i = 0; i < E; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		B.add_edge(a, b, c);
	}
	B.Bellman_solve(S, INT_MAX);
	for (int i = 0; i < V; i++) {
		if (!B.v[i].valid && B.v[i].cost != INT_MAX) {
			cout << "NEGATIVE CYCLE" << endl;
			return 0;
		}
	}
	for (int i = 0; i < V; i++) {
		if (!B.v[i].valid) cout << "INF" << endl;
		else cout << B.v[i].cost << endl;
	}
}