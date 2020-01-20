#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/12/ALDS1_12_B"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph/Dijkstra.cpp"
#include "../../template/ShortestPathGraph.cpp"

int main() {
	int n; cin >> n;
	auto G = make_shortest_path_graph(n);
	for (int i = 0; i < n; i++) {
		int v, k; cin >> v >> k;
		while (k--) {
			int u, c; cin >> u >> c;
			G.add_edge(v, u, c);
		}
	}
	Dijkstra(G, 0, INT_MAX);
	for (int i = 0; i < n; i++) {
		cout << i << " " << G.dist[i] << endl;
	}
}