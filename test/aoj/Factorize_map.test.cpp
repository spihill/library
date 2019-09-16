#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_A&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../math/Factorize.cpp"

int main() {
	int n;
	cin >> n;
	map<int, int> res;
	Factorize(n, res);
	cout << n << ":";
	for (auto& x: res) {
		for (int i = 0; i < x.second; i++) {
			cout << " " << x.first;
		}
	}
	cout << endl;
}