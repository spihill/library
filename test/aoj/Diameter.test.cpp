#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_A"

#include<bits/stdc++.h>

using namespace std;
#include "../../graph_tree/Diameter.cpp"
#include "../../template/WeightedGraph.cpp"

int main() {
	int n;
	cin >> n;
	auto G = make_weighted_graph(n);
	for (int i = 0; i < n - 1; i++) {
		int s, t, w;
		cin >> s >> t >> w;
		G.add_edge(s, t, w);
		G.add_edge(t, s, w);
	}
	cout << Diameter(G) << endl;
}
