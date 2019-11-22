#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SparseTable.cpp"

int main() {
	int N, Q;
	scanf("%d%d", &N, &Q);
	vector<int> v(N);
	for (int i = 0; i < N; i++) scanf("%d", &v[i]);
	SparseTable<int> S(
			[](int a, int b){ return min(a, b);}
			, v);
	while (Q--) {
		int l, r; scanf("%d%d", &l, &r);
		printf("%d\n", S.get(l, r));
	}
}