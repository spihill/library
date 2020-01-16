#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include<bits/stdc++.h>
using namespace std;

#include "../../datastructure/SegmentTree/DynamicSegTree.cpp"
#include "../../monoid/plus_monoid.cpp"

int main() {
	int N, Q;
	cin >> N >> Q;
	DynamicSegTree<plus_monoid<long long>> S(-2e18, 2e18, 3);
	for (int i = 0; i < Q; i++) {
		long long q, x, y; cin >> q >> x >> y;
		if (q == 0) {
			x = (x - 50000) * 1000000000LL;
			S.set(x, S[x] + y);
		} else {
			x = (x - 50000) * 1000000000LL;
			y = (y - 49999) * 1000000000LL;
			cout << S.get(x, y) - 3LL * (y - x) << endl;
		}
	}
}