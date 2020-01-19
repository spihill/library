#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/1/DSL_1_B"

#include <bits/stdc++.h>
using namespace std;

#include "../../datastructure/WeightedUnionFind.cpp"

int main() {
	int N, Q; cin >> N >> Q;
	WeightedUnionFind<int> UF(N);
	for (int i = 0; i < Q; i++) {
		int q; cin >> q;
		if (q == 0) {
			int x, y, z; cin >> x >> y >> z;
			UF.unite(x, y, z);
		} else {
			int x, y; cin >> x >> y;
			if (UF.same(x, y)) {
				cout << UF.diff(x, y) << endl;
			} else {
				cout << '?' << endl;
			}
		}
	}
}