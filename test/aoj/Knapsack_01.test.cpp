#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_B"

#include<bits/stdc++.h>

using namespace std;

#include "../../dp/Knapsack_01.cpp"

int main() {
	int n, W; cin >> n >> W;
	vector<int> v(n), w(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i] >> w[i];
	}
	cout << Knapsack_01(W, v, w) << endl;
}