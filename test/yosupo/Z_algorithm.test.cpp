#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include<bits/stdc++.h>

using namespace std;

#include "../../string/Z_algorithm.cpp"

int main() {
	string s; cin >> s;
	auto v = Z_algorithm(s);
	for (int i = 0; i < s.size(); i++) {
		cout << v[i] << " \n"[i==s.size()-1];
	}
}