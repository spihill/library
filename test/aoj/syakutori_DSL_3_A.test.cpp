#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/3/DSL_3_A"

#include <bits/stdc++.h>
using namespace std;

#include "../../algorithm/syakutori.cpp"
#include "../../snippet/monoid.cpp"

using mono = monoid<int, 0>;

template<>
mono mono::operator+(const mono& rhs) const noexcept {
	return mono(this->val + rhs.val);
}

int main() {
	int N, S; cin >> N >> S;
	vector<mono> a(N);
	for (int i = 0; i < N; i++) cin >> a[i];
	auto r = syakutori<mono>(a, [&](auto sum) {
		return sum >= S;
	}, false);
	int res = N + 1;
	for (int l = 0; l < N && r[l] <= N; l++) {
		res = min(res, r[l] - l);
	}
	if (res == N + 1) res = 0;
	cout << res << endl;
}