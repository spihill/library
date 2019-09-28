#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1501&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#define MOD 100000007
#include "../../math/ModInt.cpp"
using modint = ModInt<MOD>;
#include "../../math/ModComb.cpp"


int main() {
	int r, c;
	cin >> r >> c;
	ModComb<modint> m(r + c);
	int r1, c1, r2, c2;
	cin >> r1 >> c1 >> r2 >> c2;
	int R = abs(r1 - r2);
	int C = abs(c1 - c2);
	int mi = INT_MAX;
	modint res = 0;
	for (int i = 0; i < 2; i++) {
		int a = i ? R : r - R;
		for (int j = 0; j < 2; j++) {
			int b = j ? C : c - C;
			if (a + b < mi) res = m.C(a + b, a);
			else if (a + b == mi) res += m.C(a + b, a);
			assert(m.C(a + b, a) == m.H(b + 1, a));
			assert(m.C(a + b, a) == m.P(a + b, a) / m.P(a, a));
			mi = min(mi, a + b);
		}
	}
	cout << res << endl;
}