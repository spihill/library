#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_C"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph/WarshallFloyd.cpp"
#include "../../template/AllShortestPathGraph.cpp"

int main() {
	int V, E;
	cin >> V >> E;
	auto W = make_all_shortest_path_graph(V);
	for (int i = 0; i < E; i++) {
		int a, b, c; cin >> a >> b >> c;
		W.add_edge(a, b, c);
	}
	if (WarshallFloyd(W)) {
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				if (j) cout << " ";
				if (W.valid[i][j]) cout << W.dist[i][j];
				else cout << "INF";
			}
			cout << endl;
		}
	} else {
		cout << "NEGATIVE CYCLE" << endl;
	}
}