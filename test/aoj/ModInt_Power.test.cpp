#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_B&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#define MOD 1000000007

#include "../../math/ModInt.cpp"

using modint = ModInt<MOD>;

int main() {
	modint m;
	int n;
	cin >> m >> n;
	cout << m.power(n) << endl;
}