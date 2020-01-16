#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/DynamicSegTree.cpp"
#include "../../monoid/affine_monoid.cpp"
#include "../../math/ModInt.cpp"

using modint = ModInt<998244353>;
using monoid = affine_monoid<modint>;

vector<long long> random_index(int N) {
	mt19937 mt(1);
	uniform_int_distribution<long long> ui(-(1LL << 60), 1LL << 60);
	set<long long> s;
	while (s.size() != N) {
		s.insert(ui(mt));
	}
	vector<long long> res;
	for (auto x : s) res.push_back(x);
	return res;
}

int main() {
	int N, Q; cin >> N >> Q;
	vector<long long> index = random_index(N+1);
	DynamicSegTree<monoid> Seg(-(1LL << 60), 1LL << 60);
	for (int i = 0; i < N; i++) {
		int a, b; cin >> a >> b;
		Seg.set(index[i], {a, b});
	}
	for (int i = 0; i < Q; i++) {
		int q; cin >> q;
		if (q == 0) {
			int p, c, d; cin >> p >> c >> d;
			Seg.set(index[p], {c, d});
		} else {
			int l, r;
			modint x;
			cin >> l >> r >> x;
			auto t = Seg.get(index[l], index[r]);
			cout << t.first * x + t.second << endl;
		}
	}
}