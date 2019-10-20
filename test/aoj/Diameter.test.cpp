#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph_tree/Diameter.cpp"

int main() {
	int n;
	cin >> n;
	graph<long long> G(n);
	for (int i = 0; i < n - 1; i++) {
		int s, t, w;
		cin >> s >> t >> w;
		G.add_edge(s, t, w);
		G.add_edge(t, s, w);
	}
	cout << Diameter(G) << endl;
}
