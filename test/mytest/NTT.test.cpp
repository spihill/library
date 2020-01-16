#define IGNORE
#include<bits/stdc++.h>
using namespace std;

#include "../../math/NTT.cpp"
#include "../../math/ModInt.cpp"
#include "../../tools/RandomClass.cpp"

#define reps(i, n, m) for (int i = (int) (n); i < (int) (m); i++)
#define rep(i, n) reps(i, 0, n)

constexpr NTT_PRIMES primes;
constexpr int sz = sizeof(primes.arr) / sizeof(*(primes.arr));
constexpr bool DEBUG_PRINT = false;

#define check_all() \
	do {\
		check(0);  check(1);  check(2);  check(3);  check(4);  \
		check(5);  check(6);  check(7);  check(8);  check(9);  \
		check(10); check(11); check(12); check(13); check(14); \
		check(15); check(16); check(17); check(18); check(19); \
		check(20); check(21); check(22); check(23); check(24); \
	} while (0)

void check_long_array(int N, int M) {
	if (DEBUG_PRINT) cout << "Check long array NTT" << endl;
	RandomClass<long long> rd;
	vector<long long> A(N);
	vector<long long> B(M);
	rep(i, N) A[i] = rd.make_random(0, 3);
	rep(i, M) B[i] = rd.make_random(0, 3);
	vector<long long> C, C2;
	ANY_MOD_NTT<1000000007> ntt;
	ntt.convolution(A, B, C);
	vector<bool> checked(sz, false);
	int count = 0;
#define check(x) \
	do {\
		NTT<x> ntt2; \
		ntt2.convolution(A, B, C2); \
		assert(C2.size() == C.size()); \
		assert(C == C2); \
		constexpr int mod = primes.arr[x][0]; \
		constexpr int g = primes.arr[x][1]; \
		count++; \
		checked[x] = true; \
		if (DEBUG_PRINT) cout << "	Finished NTT<" << x << "> test (mod: " << mod << ", primitive_root: " << g << ")" << endl; \
	} while (0)
	check_all();
#undef check
	assert(count == sz);
	rep(i, sz) assert(checked[i]);
}

void check_short_array(int N, int M) {
	if (DEBUG_PRINT) cout << "Check short array NTT" << endl;
	RandomClass<long long> rd;
	vector<long long> A(N);
	vector<long long> B(M);
	rep(i, N) A[i] = rd.make_random(LLONG_MIN, LLONG_MAX);
	rep(i, M) B[i] = rd.make_random(LLONG_MIN, LLONG_MAX);
	vector<long long> C1, C2, C3;
	vector<bool> checked(sz, false);
	int count = 0;
#define check(idx) \
	do {\
		constexpr int mod = primes.arr[idx][0]; \
		constexpr int g = primes.arr[idx][1]; \
		NTT<idx> ntt1; \
		ntt1.convolution(A, B, C1); \
		ANY_MOD_NTT<mod> ntt2; \
		ntt2.convolution(A, B, C2); \
		assert(C1.size() == C2.size()); \
		assert(C1 == C2); \
		using modint = ModInt<mod>; \
		C3.clear(); C3.resize(N+M-1); \
		rep(i, N+M-1) { \
			reps(j, max(0, i+1-M), min(N, i+1)) { \
				C3[i] = (C3[i] + modint(A[j]) * B[i-j]).x; \
			} \
		} \
		assert(C1 == C3); \
		count++; \
		checked[idx] = true; \
		if (DEBUG_PRINT) cout << "	Finished NTT<" << idx << "> test (mod: " << mod << ", primitive_root: " << g << ")" << endl; \
	} while (0)
	check_all();
#undef check
	assert(count == sz);
	rep(i, sz) assert(checked[i]);
}

int main() {
	RandomClass<int> rd;
	cout << "NTT_PRIMES size : " << sz << endl;
	{
		int N = rd.make_random(1 << 18, 1 << 19);
		int M = rd.make_random(1 << 18, 1 << 19);
		int cnt = 1;
		cout << "Testing long " << cnt++ << endl;
		check_long_array(N, M);
		cout << "Testing long " << cnt++ << endl;
		check_long_array(M, N);
		cout << "Testing long " << cnt++ << endl;
		check_long_array(N, N);
	}
	rep(i, 10) {
		int N = rd.make_random(250, 750);
		int M = rd.make_random(250, 750);
		cout << "Testing short " << i + 1 << endl;
		check_short_array(N, M);
		check_short_array(M, N);
		check_short_array(N, N);
	}
}