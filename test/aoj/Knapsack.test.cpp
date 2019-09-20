#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_C"

#include<bits/stdc++.h>

using namespace std;

#include "../../dp/Knapsack.cpp"

int main() {
	int n, W; cin >> n >> W;
	vector<int> v(n), w(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i] >> w[i];
	}
	cout << Knapsack(W, v, w) << endl;
}