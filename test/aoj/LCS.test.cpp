#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_C&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../dp/LCS.cpp"

int main() {
	int n; cin >> n;
	while (n--) {
		string s, t;
		cin >> s >> t;
		cout << LCS(s, t) << endl;
	}
}