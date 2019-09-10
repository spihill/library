#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph/Dijkstra.cpp"

int main() {
	int V, E, S;
	cin >> V >> E >> S;
	Dijkstra<int> D(V);
	for (int i = 0; i < E; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		D.add_edge(a, b, c);
	}
	D.Dijkstra_solve(S, INT_MAX);
	for (int i = 0; i < V; i++) {
		if (D.v[i].cost == INT_MAX) cout << "INF" << endl;
		else cout << D.v[i].cost << endl;
	}
}