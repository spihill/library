#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/LazySegmentTree.cpp"
#include "../../datastructure/SegmentTree/RSQ_RAQ.cpp"


int main() {
	int n, Q;
	cin >> n >> Q;
	using ll = long long;
	LazySegmentTree<RSQ_RAQ<ll, ll>> L(n);
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