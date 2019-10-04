#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/SegmentTree.cpp"
#include "../../datastructure/SegmentTree/RMQ.cpp"


int main() {
	int n, Q;
	cin >> n >> Q;
	vector<int> v(n, INT_MAX);
	SegmentTree<RMQ<int>> S(n);
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
	SegmentTree<RMQ<int>> T(v);
	assert(T.n == S.n);
	assert((int) T.node.size() == T.n*2-1);
	assert((int) S.node.size() == S.n*2-1);
	for (int i = 0; i < 2*n-1; i++) {
		assert(S.node[i].val == T.node[i].val);
	}
}