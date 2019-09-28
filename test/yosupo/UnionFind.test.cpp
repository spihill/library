#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/UnionFind.cpp"

int main() {
	int N, Q;
	cin >> N >> Q;
	UnionFind U(N);
	while (Q--) {
		int q, u, v;
		cin >> q >> u >> v;
		if (q == 0) {
			U.unite(u, v);
		} else {
			cout << U.same(u, v) << endl;
		}
	}
}