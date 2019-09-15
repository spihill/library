#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B&lang=jp"

#include<bits/stdc++.h>

using namespace std;

#define MOD 1

#include "../../math/ModInt.cpp"
#include "../../string/RollingHash.cpp"

int main() {
	string a, b;
	cin >> a >> b;
	RollingHash<> R(a), L(b);
	for(int i = 0; i + b.size() <= a.size(); i++) {
	if(R.get(i, i + b.size()) == L.get(0, b.size())) {
		cout << i << endl;
	}
  }
}