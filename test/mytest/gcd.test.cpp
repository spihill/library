#define IGNORE
#include<bits/stdc++.h>

using namespace std;

#include "../../tools/RandomClass.cpp"
#include "../../math/gcd.cpp"
#include "../../math/Factorize.cpp"

template<class T>
bool check(T a, T b) {
	T g = gcd(a, b);
	map<T, int> A, B;
	Factorize(a, A);
	Factorize(b, B);
	map<T, int> G = gcd(A, B);
	T g2 = 1;
	for (auto x : G) {
		while (x.second--) {
			g2 *= x.first;
		}
	}
	return g == g2;
}

int main() {
	random_class rd;
	cout << "start gcd test" << endl;

	cout << "small test" << endl;
	for (int i = 1; i < 1000; i++) {
		for (int j = 1; j < 1000; j++) {
			assert(check(i, j));
		}
	}

	cout << "large test" << endl;
	for (int i = 1; i < 1000; i++) {
		long long a = rd.make_random<long long>(1, 100000000000000);
		long long b = rd.make_random<long long>(1, 100000000000000);
		assert(check(a, b));
	}
}