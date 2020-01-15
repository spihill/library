#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_C"

#include<bits/stdc++.h>
using namespace std;

#include "../../math/lcm.cpp"

int main() {
	long long res = 1;
	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		long long a; cin >> a;
		res = lcm(res, a);
	}
	cout << res << endl;
}