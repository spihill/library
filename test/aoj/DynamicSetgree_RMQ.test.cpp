#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/DynamicSegTree.cpp"
#include "../../monoid/min_monoid.cpp"

int main() {
	int N, Q;
	cin >> N >> Q;
	DynamicSegTree<min_monoid<int>> S(-100, N+100);
	for (int i = 0; i < Q; i++) {
		int q, x, y; cin >> q >> x >> y;
		if (q == 0) {
			x -= 50;
			S.set(x, y);
		} else {
			x -= 50; y -= 50;
			y++;
			cout << S.get(x, y) << endl;
		}
	}
}