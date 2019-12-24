#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/3/DSL_3_C"

#include <bits/stdc++.h>
using namespace std;

#include "../../algorithm/syakutori.cpp"
#include "../../snippet/monoid.cpp"

using mono = monoid<long long, 0>;

template<>
mono mono::operator+(const mono& rhs) const noexcept {
	return mono(this->val + rhs.val);
}

int main() {
	int N, Q; cin >> N >> Q;
	vector<mono> a(N);
	for (int i = 0; i < N; i++) cin >> a[i];
	while (Q--) {
		long long x; cin >> x;
		auto r = syakutori<mono>(a, [&](auto n) {
			return n <= x;
		});
		long long res = 0;
		for (int l = 0; l < N; l++) res += r[l] - l;
		cout << res << endl;
	}
	return 0;
}