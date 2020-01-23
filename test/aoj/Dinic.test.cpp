#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../template/FlowGraph.cpp"
#include "../../graph/Dinic.cpp"

int main() {
	int n, m;
	cin >> n >> m;
	auto G = make_flow_graph<long long>(n);
	for (int i = 0; i < m; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		G.add_edge(u, v, c);
	}
	cout << Dinic(G, 0, n-1) << endl;
}