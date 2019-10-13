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
	ANY_MOD_NTT<998244353> ntt;
	auto c = ntt.convolution(a, b);
	for (int i = 0; i < N + M - 1; i++) {
		if (i) cout << " ";
		cout << c[i];
	}
	cout << endl;
}
