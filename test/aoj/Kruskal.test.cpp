#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=jp"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph/Kruskal.cpp"
#include "../../template/WeightedGraph.cpp"

int main() {
	int V, E;
	cin >> V >> E;
	auto G = make_weighted_graph(V);
	for (int i = 0; i < E; i++) {
		int s, t, w;
		cin >> s >> t >> w;
		G.add_edge(s, t, w);
		G.add_edge(t, s, w);
	}
	cout << Kruskal(G) << endl;
}