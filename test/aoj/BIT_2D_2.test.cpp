#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1125"

#include<bits/stdc++.h>
using namespace std;

#include "../../datastructure/BIT_2D.cpp"

int solve(int N) {
	int H, W; cin >> H >> W;
	vector<vector<int>> v(H, vector<int>(W, 0));
	for (int i = 0; i < N; i++) {
		int a, b; cin >> a >> b; v[a-1][b-1] = 1;
	}
	BIT_2D<int> bit(v);
	int S, T; cin >> S >> T;
	int res = 0;
	for (int i = 0; i < H-S+1; i++) for (int j = 0; j < W-T+1; j++) {
		res = max(res, bit.get_sum(i, j, i+S, j+T));
	}
	return res;
}

int main() {
	int n;
	while (cin >> n, n) cout << solve(n) << endl;
}

