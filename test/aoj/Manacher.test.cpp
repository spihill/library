#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2934"

#include<bits/stdc++.h>

using namespace std;

#include "../../string/Manacher.cpp"

int solve() {
	int N; cin >> N;
	string s;
	vector<int> ss;

	for (int i = 0; i < N; i++) {
		char c; cin >> c;
		s += c; s += '$';
		ss.push_back(c);
		ss.push_back('$');
	}
	s.pop_back();
	ss.pop_back();
	assert(s.size() == ss.size());
	auto mn = manacher(s);
	auto mn2 = manacher(ss);
	for (size_t i = 0; i < mn.size(); i++) {
		assert(mn[i] == mn2[i]);
	}
	for (int i = 2; i < N * 2; i += 2) {
		int p;
		for (p = i; mn[p] == p + 1; p += mn[p] - 1);
		if (p + mn[p] == N * 2 - 1) return i / 2 + 1;
	}
	assert(0);
}

int main() {
	cout << solve() << endl;
}