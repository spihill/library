#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/BIT.cpp"

int main() {
	int n, Q; cin >> n >> Q;
	BIT<long long> B(n+1);
	for (int i = 0; i < n; i++) {
		int x; cin >> x; B.add(i, x);
	}
	while (Q--) {
		int q; cin >> q;
		if (q) {
			int l, r; cin >> l >> r; cout << B.get(r) - B.get(l) << endl;
		} else {
			int p, x; cin >> p >> x;
			B.add(p, x);
		}
	}
}

