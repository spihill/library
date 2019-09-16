#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_B&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../algorithm/meguru.cpp"

int main() {
	int n, m;
	cin >> n;
	vector<int> S(n+1, -1);
	for (int i = 0; i < n; i++) cin >> S[i+1];
	S.push_back(INT_MAX);
	cin >> m;
	int res = 0;
	for (int i = 0; i < m; i++) {
		int a;
		cin >> a;
		auto isok = [&](int x) -> bool {
			return S[x] <= a;
		};
		int x = meguru<int>(0, n+1, isok);
		res += S[x] == a;
	}
	cout << res << endl;
}