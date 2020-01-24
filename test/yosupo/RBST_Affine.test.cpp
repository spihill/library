#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/RBST.cpp"
#include "../../monoid/affine_monoid.cpp"
#include "../../math/ModInt.cpp"

using modint = ModInt<998244353>;
using monoid = affine_monoid<modint>;

int main() {
	int N, Q; cin >> N >> Q;
	RBST<long long, monoid> R;
	for (int i = 0; i < N; i++) {
		int a, b; cin >> a >> b;
		R.set(i, {a, b});
	}
	for (int i = 0; i < Q; i++) {
		int q; cin >> q;
		if (q == 0) {
			int p, c, d; cin >> p >> c >> d;
			R.set(p, {c, d});
		} else {
			int l, r;
			modint x;
			cin >> l >> r >> x;
			auto t = R.get(l, r);
			cout << t.first * x + t.second << endl;
		}
	}
}