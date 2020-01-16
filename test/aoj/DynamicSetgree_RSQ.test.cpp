#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include<bits/stdc++.h>
using namespace std;

#include "../../datastructure/SegmentTree/DynamicSegTree.cpp"
#include "../../monoid/plus_monoid.cpp"

int main() {
	int N, Q;
	cin >> N >> Q;
	DynamicSegTree<plus_monoid<int>> S(-2e18, 2e18, 3);
	for (int i = 0; i < Q; i++) {
		int q, x, y; cin >> q >> x >> y;
		if (q == 0) {
			x -= 50;
			S.set(x, S[x] + y);
		} else {
			x -= 50; y -= 50;
			y++;
			cout << S.get(x, y) - 3 * (y - x) << endl;
		}
	}
}