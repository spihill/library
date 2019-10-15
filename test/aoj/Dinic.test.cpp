#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph/Dinic.cpp"

int main() {
	int n, m;
	cin >> n >> m;
	dinic<int> D(n);
	for (int i = 0; i < m; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		D.add_edge(u, v, c);
	}
	cout << D.solve(0, n-1) << endl;
}