#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/RBST.cpp"
#include "../../monoid/plus_monoid.cpp"

int main() {
	int N, Q;
	scanf("%d %d", &N, &Q);
	RBST<long long, plus_monoid<long long>> R;
	while (Q--) {
		int q, x, y;
		scanf("%d %d %d", &q, &x, &y);
		if (q == 0) {
			x--;
			R.set(x, R.get(x, x+1) + y);
		} else {
			x--;
			y--;
			printf("%lld\n", R.get(x, y+1));
		}
	}
	return 0;
}