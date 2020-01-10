#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=jp"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph/FibPrim.cpp"

int main() {
	int V, E;
	cin >> V >> E;
	graph<int> P(V);
	for (int i = 0; i < E; i++) {
		int s, t, w;
		cin >> s >> t >> w;
		P.add_edge(s, t, w);
		P.add_edge(t, s, w);
	}
	cout << FibPrim(P) << endl;
}