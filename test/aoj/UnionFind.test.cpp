#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_11_D&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/UnionFind.cpp"

int main() {
	int n, m;
	cin >> n >> m;
	UnionFind uf(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		uf.unite(a, b);
	}
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		if (uf.same(a, b)) cout << "yes" << endl;
		else cout << "no" << endl;
	}
}