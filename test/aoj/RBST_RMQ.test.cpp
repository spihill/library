#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/RBST.cpp"
#include "../../monoid/min_monoid.cpp"


int main() {
	int n, Q;
	cin >> n >> Q;
	RBST<int, min_monoid<int>> R;
	while (Q--) {
		int q, x, y;
		cin >> q >> x >> y;
		if (q == 0) {
			R.set(x, y);
		} else {
			cout << R.get(x, y+1) << endl;
		}
	}
}