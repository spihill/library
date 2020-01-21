#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph/Bellmanford.cpp"
#include "../../template/ShortestPathGraph.cpp"

int main() {
	int V, E, S;
	cin >> V >> E >> S;
	auto G = make_shortest_path_graph(V);
	for (int i = 0; i < E; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		G.add_edge(a, b, c);
	}
	Bellmanford(G, S, INT_MAX);
	for (int i = 0; i < V; i++) {
		if (!G.valid[i] && G.dist[i] != INT_MAX) {
			cout << "NEGATIVE CYCLE" << endl;
			return 0;
		}
	}
	for (int i = 0; i < V; i++) {
		if (!G.valid[i]) cout << "INF" << endl;
		else cout << G.dist[i] << endl;
	}
}