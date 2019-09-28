#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_H"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/LazySegmentTree.cpp"


int main() {
	int n, Q;
	cin >> n >> Q;
	using ll = long long;
	LazySegmentTree<ll, ll> L(
			[](ll a, ll b){return min(a, b);},
			[](ll a, ll b){return a + b;},
			[](ll a, ll b){return a + b;},
			[](ll a, int len){return a;},
			LLONG_MAX,
			0
	);
	L.build(vector<ll>(n, 0));
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