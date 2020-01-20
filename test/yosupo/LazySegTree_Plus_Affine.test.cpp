#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/LazySegmentTree.cpp"
#include "../../math/ModInt.cpp"
using modint = ModInt<998244353>;
#include "../../monoid/pair/plus_affine_monoid.cpp"
using monoid = plus_affine_monoid<modint>;

int main() {
	int N, Q; cin >> N >> Q;
	vector<modint> v(N);
	for (int i = 0; i < N; i++) cin >> v[i];
	LazySegmentTree<monoid> Seg(v);
	for (int i = 0; i < Q; i++) {
		int q; cin >> q;
		if (q == 0) {
			int l, r, b, c; cin >> l >> r >> b >> c;
			Seg.set(l, r, {b, c});
		} else {
			int l, r;
			cin >> l >> r;
			cout << Seg.get(l, r) << endl;
		}
	}
}