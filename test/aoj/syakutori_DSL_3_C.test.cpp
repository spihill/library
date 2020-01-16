#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/3/DSL_3_C"

#include <bits/stdc++.h>
using namespace std;

#include "../../algorithm/syakutori.cpp"

#include "../../monoid/plus_monoid.cpp"

using monoid = plus_monoid<long long>;

int main() {
	int N, Q; cin >> N >> Q;
	vector<monoid> a(N);
	for (int i = 0; i < N; i++) cin >> a[i];
	while (Q--) {
		long long x; cin >> x;
		auto r = syakutori<monoid>(a, [&](auto n) {
			return n <= x;
		});
		long long res = 0;
		for (int l = 0; l < N; l++) res += r[l] - l;
		cout << res << endl;
	}
	return 0;
}