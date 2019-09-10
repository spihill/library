#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_6_D&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../math/Matrix.cpp"

int main() {
	int n, m;
	cin >> n >> m;
	Matrix<int> A(n, m), B(m, 1);
	cin >> A >> B;
	cout << A * B << endl;
}