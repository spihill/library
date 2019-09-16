#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_D&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../algorithm/meguru.cpp"

int main() {
	int n, k;
	cin >> n >> k;
	vector<int> v(n);
	for (auto& x: v) cin >> x;
	auto isok = [&](int x) -> bool {
		int cnt = 1;
		int w = 0;
		for (int i = 0; i < n && cnt <= k; i++) {
			w += v[i];
			if (w > x) w = 0, cnt++, i--;
		}
		return cnt <= k;
	};
	cout << meguru<int>(INT_MAX, 0, isok) << endl;
}