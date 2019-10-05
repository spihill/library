#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include<bits/stdc++.h>

using namespace std;

#include "../../math/NTT.cpp"

int main() {
	int N, M;
	cin >> N >> M;
	vector<long long> a(N), b(M);
	for (int i = 0; i < N; i++) cin >> a[i];
	for (int i = 0; i < M; i++) cin >> b[i];
	auto c = mod_convolution(a, b, 998244353);
	for (int i = 0; i < N + M - 1; i++) {
		if (i) cout << " ";
		cout << c[i];
	}
	cout << endl;
}
