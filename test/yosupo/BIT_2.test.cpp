#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/BIT.cpp"

int main() {
	int n, Q; cin >> n >> Q;
	vector<long long> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	BIT<long long> B(v);
	while (Q--) {
		int q; cin >> q;
		if (q) {
			int l, r; cin >> l >> r; cout << B.get(l, r) << endl;
		} else {
			int p, x; cin >> p >> x;
			B.add(p, x);
		}
	}
}

