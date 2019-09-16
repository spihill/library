#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=jp"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/UnionFind.cpp"
#include "../../graph/Kruskal.cpp"

int main() {
	int V, E;
	cin >> V >> E;
	Kruskal<int> K(V);
	for (int i = 0; i < E; i++) {
		int s, t, w;
		cin >> s >> t >> w;
		K.Kruskal_add_edge(s, t, w);
		K.Kruskal_add_edge(t, s, w);
	}
	cout << K.Kruskal_solve() << endl;
}