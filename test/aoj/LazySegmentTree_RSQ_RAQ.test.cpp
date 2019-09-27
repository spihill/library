#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/LazySegmentTree.cpp"


int main() {
	int n, Q;
	cin >> n >> Q;
	using ll = long long;
	LazySegmentTree<ll, ll> L(n,
			[](ll a, ll b){return a + b;},
			[](ll a, ll b){return a + b;},
			[](ll a, ll b){return a + b;},
			[](ll a, int len){return a * len;},
			0,
			0
	);
	while (Q--) {
		int q;
		cin >> q;
		if (q == 0) {
			int s, t, x; cin >> s >> t >> x; s--; t--;
			L.set(s, t+1, x);
		} else {
			int s, t; cin >> s >> t; s--; t--;
			cout << L.get(s, t+1) << endl;
		}
	}
}