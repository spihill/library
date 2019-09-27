#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_F"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/LazySegmentTree.cpp"


int main() {
	int n, Q;
	cin >> n >> Q;
	LazySegmentTree<int, int> L(n,
			[](int a, int b){return min(a, b);},
			[](int a, int b){return (b >= 0 ? b : a);},
			[](int a, int b){return (b >= 0 ? b : a);},
			[](int a, int len){return a;},
			INT_MAX,
			-1
	);
	while (Q--) {
		int q;
		cin >> q;
		if (q == 0) {
			int s, t, x; cin >> s >> t >> x;
			L.set(s, t+1, x);
		} else {
			int s, t; cin >> s >> t;
			cout << L.get(s, t+1) << endl;
		}
	}
}