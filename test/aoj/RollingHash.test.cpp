#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B&lang=jp"

#include<bits/stdc++.h>

using namespace std;

#include "../../string/RollingHash.cpp"

int main() {
	string a, b;
	cin >> a >> b;
	RollingHash<1000000> R(a);
	RollingHash<10000> L(b);
	for(int i = 0; i + b.size() <= a.size(); i++) {
		if(R.get(i, i + b.size()) == L.get(0, b.size())) {
			cout << i << endl;
		}
	}
}