#include <bits/stdc++.h>

using namespace std;

#include "../../math/ModInt.cpp"

#define RANGE_CHECK(a) assert(0 <= (a).x && (a).x < (a).M)

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
	ostream& os;
	random_class(ostream& o) : rd(), xor128(rd()), os(o) {}
	long long make_random(long long min_v, long long max_v) { return uniform_int_distribution<long long>(min_v, max_v)(xor128);}
};

template<class M>
void test(M a) {
	random_class R(cout);
	a = LLONG_MIN;
	RANGE_CHECK(a);
	a = LLONG_MAX;
	RANGE_CHECK(a);
	for (int i = 0; i < 100; i++) {
		a = R.make_random(LLONG_MIN, LLONG_MAX); RANGE_CHECK(a);
		M b = R.make_random(LLONG_MIN, LLONG_MAX); RANGE_CHECK(b);
		M c;
		M d = a;
		c = a + b; RANGE_CHECK(c); assert((d += b) == c); assert(!(d != c)); d = a;
		c = a - b; RANGE_CHECK(c); assert((d -= b) == c); assert(!(d != c)); d = a;
		c = a / b; RANGE_CHECK(c); assert((d /= b) == c); assert(!(d != c)); d = a;
		c = a * b; RANGE_CHECK(c); assert((d *= b) == c); assert(!(d != c)); d = a;
		long long B = R.make_random(LLONG_MIN, LLONG_MAX);
		M C;
		M D = a; RANGE_CHECK(D);
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
		M b = R.make_random(LLONG_MIN, LLONG_MAX);
		M c;
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
		M t = a; RANGE_CHECK(t);
		M d;
		c = a++; d = t; RANGE_CHECK(c); RANGE_CHECK(d); assert(c == d);
		c = a; d = ++t; RANGE_CHECK(c); RANGE_CHECK(d); assert(c == d);
		c = a--; d = t; RANGE_CHECK(c); RANGE_CHECK(d); assert(c == d);
		c = a; d = --t; RANGE_CHECK(c); RANGE_CHECK(d); assert(c == d);

	}
}

int main() {
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
}