#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_I"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/LazySegmentTree.cpp"


int main() {
	int n, Q;
	cin >> n >> Q;
	using ll = long long;
	LazySegmentTree<ll, ll> L(n,
			[](ll a, ll b){return a + b;},
			[](ll a, ll b){return b;},
			[](ll a, ll b){return b;},
			[](ll a, int len){return a * len;},
			0,
			INT_MAX
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