#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_E&lang=jp"

#include<bits/stdc++.h>

using namespace std;

#include "../../math/extgcd.cpp"

int main() {
	int a, b;
	cin >> a >> b;
	int x, y;
	extgcd(a, b, x, y);
	cout << x << " " << y << endl;
}
