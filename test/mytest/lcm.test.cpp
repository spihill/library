#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"
#include<bits/stdc++.h>

using namespace std;

#include "../../tools/RandomClass.cpp"
#include "../../math/lcm.cpp"
#include "../../math/gcd.cpp"
#include "../../math/Factorize.cpp"
#include "../../math/ModInt.cpp"
using modint = ModInt<1000000007>;

template<class T>
bool check(T a, T b) {
	modint l = modint(a) / gcd(a, b) * b;
	map<T, int> A, B;
	Factorize(a, A);
	Factorize(b, B);
	map<T, int> L = lcm(A, B);
	modint l2 = 1;
	for (auto x : L) {
		while (x.second--) {
			l2 *= x.first;
		}
	}
	return l == l2;
}

int main() {
	random_class rd;
	cerr << "start lcm test" << endl;

	cerr << "small test" << endl;
	for (int i = 1; i < 1000; i++) {
		for (int j = 1; j < 1000; j++) {
			assert(check(i, j));
		}
	}

	cerr << "large test" << endl;
	for (int i = 1; i < 1000; i++) {
		long long a = rd.make_random<long long>(1, 100000000000000);
		long long b = rd.make_random<long long>(1, 100000000000000);
		assert(check(a, b));
	}
	cout << "Hello World" << endl;
}