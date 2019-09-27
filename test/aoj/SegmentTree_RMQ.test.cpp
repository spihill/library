#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/SegmentTree.cpp"


int main() {
	int n, Q;
	cin >> n >> Q;
	SegmentTree<int> S(n,
			[](int a, int b){return min(a, b);},
			[](int a, int b){return b;},
			INT_MAX
	);
	vector<int> v(n, INT_MAX);
	while (Q--) {
		int q, x, y;
		cin >> q >> x >> y;
		if (q == 0) {
			S.set(x, y);
			v[x] = y;
		} else {
			cout << S.get(x, y+1) << endl;
		}
	}
	SegmentTree<int> T(v,
			[](int a, int b){return min(a, b);},
			[](int a, int b){return b;},
			INT_MAX
	);
	assert(T.n == S.n);
	assert((int) T.node.size() == T.n*2-1);
	assert((int) S.node.size() == S.n*2-1);
	for (int i = 0; i < 2*n-1; i++) {
		assert(S.node[i] == T.node[i]);
	}
}