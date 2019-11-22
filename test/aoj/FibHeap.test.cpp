#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_9_C"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/FibHeap.cpp"

int main() {
	cin.tie(0); ios::sync_with_stdio(false);
	FibHeap<int> q;
	string s;
	while (cin >> s, s != "end") {
		if (s[0] == 'i') {
			int x; cin >> x;
			q.push(x);
		} else {
			cout << q.top() << endl;
			q.pop();
		}
	}
	q.check();
}