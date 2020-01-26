#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"
#include <bits/stdc++.h>

using namespace std;

#include "../../math/ModInt.cpp"

#define RANGE_CHECK(a) assert(0 <= (a).x && (a).x < (modint::get_mod()))

struct random_class {
	struct xorshift {
		using result_type = unsigned int;
		result_type x=123456789u,y=362436069u,z=521288629u,w;
		static constexpr result_type min() {return 0u;}
		static constexpr result_type max() {return UINT_MAX;}
		xorshift(result_type a) : w(a) {}
		result_type operator()() {
			result_type t;
			t = x ^ (x << 11);
			x = y; y = z; z = w;
			return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
		}
	};
	random_device rd;
	xorshift xor128;
	random_class() : rd(), xor128(rd()) {}
	long long make_random(long long min_v, long long max_v) { return uniform_int_distribution<long long>(min_v, max_v)(xor128);}
};

constexpr bool isprime(int m) {
	if (m < 2) return false;
	for (long long i = 2; i * i <= m; i++) {
		if (m % i == 0) return false;
	}
	return true;
}


template<class modint>
void test(modint a) {
	static_assert(isprime(modint::get_mod()), "a.M is not a prime number");
	random_class R;
	a = LLONG_MIN;
	RANGE_CHECK(a);
	a = LLONG_MAX;
	RANGE_CHECK(a);
	for (int i = 0; i < 100; i++) {
		a = R.make_random(LLONG_MIN, LLONG_MAX); RANGE_CHECK(a);
		modint b = R.make_random(LLONG_MIN, LLONG_MAX); RANGE_CHECK(b);
		modint c;
		modint d = a;
		c = a + b; RANGE_CHECK(c); assert((d += b) == c); assert(!(d != c)); d = a;
		c = a - b; RANGE_CHECK(c); assert((d -= b) == c); assert(!(d != c)); d = a;
		c = a / b; RANGE_CHECK(c); assert((d /= b) == c); assert(!(d != c)); d = a;
		c = a * b; RANGE_CHECK(c); assert((d *= b) == c); assert(!(d != c)); d = a;
		long long B = R.make_random(LLONG_MIN, LLONG_MAX);
		modint C;
		modint D = a; RANGE_CHECK(D);
		C = a + B; RANGE_CHECK(C); assert((D += B) == C); assert(!(D != C)); D = B;
		C = B + a; RANGE_CHECK(C); assert((D += a) == C); assert(!(D != C)); D = a;
		C = a - B; RANGE_CHECK(C); assert((D -= B) == C); assert(!(D != C)); D = B;
		C = B - a; RANGE_CHECK(C); assert((D -= a) == C); assert(!(D != C)); D = a;
		C = a * B; RANGE_CHECK(C); assert((D *= B) == C); assert(!(D != C)); D = B;
		C = B * a; RANGE_CHECK(C); assert((D *= a) == C); assert(!(D != C)); D = a;
		C = a / B; RANGE_CHECK(C); assert((D /= B) == C); assert(!(D != C)); D = B;
		C = B / a; RANGE_CHECK(C); assert((D /= a) == C); assert(!(D != C)); D = a;
	}
	for (int i = 0; i < 100; i++) {
		a = R.make_random(LLONG_MIN, LLONG_MAX);
		modint b = R.make_random(LLONG_MIN, LLONG_MAX);
		modint c;
		c = a + b - b; RANGE_CHECK(c); assert(c == a);
		c = b + a - a; RANGE_CHECK(c); assert(c == b);
		c = -a; RANGE_CHECK(c); assert(c == 0 - a);
		c = +a; RANGE_CHECK(c); assert(c == a);
		if (b != 0) {
			assert(a * b / b == a);
			assert(b / b == 1);
		}
		if (a != 0) {
			assert(b * a / a == b);
			assert(a / a == 1);
		}
		modint t = a; RANGE_CHECK(t);
		modint d;
		c = a++; d = t; RANGE_CHECK(c); RANGE_CHECK(d); assert(c == d);
		c = a; d = ++t; RANGE_CHECK(c); RANGE_CHECK(d); assert(c == d);
		c = a--; d = t; RANGE_CHECK(c); RANGE_CHECK(d); assert(c == d);
		c = a; d = --t; RANGE_CHECK(c); RANGE_CHECK(d); assert(c == d);
	}
}

void check_literal() {
	cerr << "ModInt<1000000007> is literal_type" << endl;
	static_assert(is_literal_type<ModInt<2>>::value, "");
	using modint = ModInt<1000000007>;
	static_assert(modint(1) / 2 == 500000004, "");
	static_assert(modint(1) + 2 == 3, "");
	static_assert(modint(1) - 2 == 1000000006, "");
	static_assert(modint(1) * 2 == 2, "");
	static_assert(+modint(1) == 1, "");
	static_assert(-modint(1) == 1000000006, "");
	static_assert(++modint(1) == 2, "");
	static_assert(modint(1)++ == 1, "");
	static_assert(--modint(1) == 0, "");
	static_assert(modint(1)-- == 1, "");
	static_assert(modint(2) == (modint(1) = 2), "");
	static_assert(modint(2).power(2) == 4, "");
	static_assert(modint(2).inv() == 500000004, "");
	static_assert(modint(2) != 1, "");
	static_assert(modint(2) == 2, "");
	static_assert(static_cast<int>(modint(2)) == 2, "");

	static_assert(is_same<decltype(modint(1) + 1), modint>::value, "");
	static_assert(is_same<decltype(1 + modint(1)), modint>::value, "");
	static_assert(is_same<decltype(modint(1) + modint(1)), modint>::value, "");
	static_assert(is_same<decltype(+modint(1)), modint>::value, "");
	static_assert(is_same<decltype(modint(1) += 1), modint&>::value, "");
	static_assert(is_same<decltype(modint(1)++), modint>::value, "");
	static_assert(is_same<decltype(++modint(1)), modint&>::value, "");

	static_assert(is_same<decltype(modint(1) - 1), modint>::value, "");
	static_assert(is_same<decltype(1 - modint(1)), modint>::value, "");
	static_assert(is_same<decltype(modint(1) - modint(1)), modint>::value, "");
	static_assert(is_same<decltype(-modint(1)), modint>::value, "");
	static_assert(is_same<decltype(modint(1) -= 1), modint&>::value, "");
	static_assert(is_same<decltype(modint(1)--), modint>::value, "");
	static_assert(is_same<decltype(--modint(1)), modint&>::value, "");

	static_assert(is_same<decltype(modint(1) * 1), modint>::value, "");
	static_assert(is_same<decltype(1 * modint(1)), modint>::value, "");
	static_assert(is_same<decltype(modint(1) * modint(1)), modint>::value, "");
	static_assert(is_same<decltype(modint(1) *= 1), modint&>::value, "");

	static_assert(is_same<decltype(modint(1) / 1), modint>::value, "");
	static_assert(is_same<decltype(1 / modint(1)), modint>::value, "");
	static_assert(is_same<decltype(modint(1) / modint(1)), modint>::value, "");
	static_assert(is_same<decltype(modint(1) /= 1), modint&>::value, "");

	static_assert(is_integral<modint>::value, "");
	static_assert(is_scalar<modint>::value, "");
	static_assert(!is_floating_point<modint>::value, "");
	static_assert(!is_signed<modint>::value, "");
	static_assert(is_unsigned<modint>::value, "");
}

int main() {
	check_literal();
	for (int i = 0; i < 100; i++) {
		test(ModInt<1811939329>(0));
		test(ModInt<1711276033>(0));
		test(ModInt<1000000007>(0));
		test(ModInt<1000000009>(0));
		test(ModInt<998244353>(0));
		test(ModInt<10007>(0));
		test(ModInt<10009>(0));
		test(ModInt<2>(0));
		test(ModInt<3>(0));
		test(ModInt<5>(0));
		test(ModInt<7>(0));
		test(ModInt<11>(0));
		test(ModInt<13>(0));
		test(ModInt<97>(0));
	}
	cout << "Hello World" << endl;
}