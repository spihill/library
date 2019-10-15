#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=jp"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph/Kruskal.cpp"

int main() {
	int V, E;
	cin >> V >> E;
	graph<int> K;
	for (int i = 0; i < E; i++) {
		int s, t, w;
		cin >> s >> t >> w;
		K.add_edge(s, t, w);
		K.add_edge(t, s, w);
	}
	cout << Kruskal(K) << endl;
}