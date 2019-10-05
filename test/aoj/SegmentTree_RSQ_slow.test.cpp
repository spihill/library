#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/SegmentTree_slow.cpp"
#include "../../datastructure/SegmentTree/RSQ_slow.cpp"

int main() {
	int N, Q;
	scanf("%d %d", &N, &Q);
	vector<long long> v(N, 0);
	SegmentTree_slow<RSQ_slow<>> S(v);
	while (Q--) {
		int q, x, y;
		scanf("%d %d %d", &q, &x, &y);
		if (q == 0) {
			x--;
			S.set(x, y);
		} else {
			x--;
			y--;
			printf("%lld\n", S.get(x, y+1));
		}
	}
	return 0;
}