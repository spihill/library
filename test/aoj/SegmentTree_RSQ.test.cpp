#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/SegmentTree.cpp"

int main() {
	int n, Q;
	cin >> n >> Q;
	vector<int> v(n, 0);
	SegmentTree<int> S(n,
			[](int a, int b){return a + b;},
			[](int a, int b){return a + b;},
			0
	);
	while (Q--) {
		int q, x, y;
		cin >> q >> x >> y;
		if (q == 0) {
			x--;
			S.set(x, y);
			v[x] += y;
		} else {
			x--; y--;
			cout << S.get(x, y+1) << endl;
		}
	}
	SegmentTree<int> T(v,
			[](int a, int b){return a + b;},
			[](int a, int b){return a + b;},
			0
	);
	assert(S.n == T.n);
	assert((int) T.node.size() == T.n*2-1);
	assert((int) S.node.size() == S.n*2-1);
	for (int i = 0; i < 2*n-1; i++) assert(S.node[i] == T.node[i]);
}