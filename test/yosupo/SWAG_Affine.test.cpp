#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SWAG.cpp"
#include "../../monoid/affine_monoid.cpp"
#include "../../math/ModInt.cpp"

using modint = ModInt<998244353>;
using monoid = affine_monoid<modint>;

int main() {
	int Q; cin >> Q;
	SWAG<monoid> S;
	for (int i = 0; i < Q; i++) {
		int q; cin >> q;
		if (q == 0) {
			int a, b; cin >> a >> b;
			S.push({a, b});
		} else if (q == 1) {
			S.pop();
		} else if (q == 2) {
			modint x; cin >> x;
			auto res = S.fold_all();
			cout << res.first * x + res.second << endl;
		}
	}
}