#define IGNORE
#include <bits/stdc++.h>

using namespace std;

#include "../../datastructure/BinarySearchTree/develop/Treap.cpp"

struct xorshift {
	using result_type = uint_fast32_t;
	result_type x=123456789u,y=362436069u,z=521288629u,w = 88675123u;
	static constexpr result_type min() {return numeric_limits<result_type>::min();}
	static constexpr result_type max() {return numeric_limits<result_type>::max();}
	xorshift() {}
	result_type operator()() {
		result_type t;
		t = x ^ (x << 11);
		x = y; y = z; z = w;
		return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
	}
};

using u32 = uint_fast32_t;
using i32 = int_fast32_t;
using i64 = int_fast64_t;
using type = u32;

template<class Compare> void check_small_size_queries(const u32 N, const u32 Q, Compare C, const i64 sup_value = -1);
template<class Compare> void check_compare_with_multiset(const TreapSet<type, Compare>& T, const multiset<type, Compare>& S);
vector<type> make_random_vector(const u32 N, const i64 sup_value);
type make_random(const i64 sup_value);

int main() {
	check_small_size_queries(300, 100, less<type>(), 20);
	check_small_size_queries(300, 100, less<type>());
	check_small_size_queries(300, 100, greater<type>(), 20);
	check_small_size_queries(300, 100, greater<type>());
}

template<class Compare> void check_small_size_queries(const u32 N, const u32 Q, Compare C, const i64 sup_value) {
	TreapSet<type, Compare> T;
	for (u32 cnt = 0; cnt < Q; cnt++) {
		vector<type> r = make_random_vector(N, sup_value);
		std::multiset<type, Compare> S;
		for (u32 i = 0; i < N; i++) {
			T.insert(r[i]);
			S.insert(r[i]);
			T.check();
			check_compare_with_multiset(T, S);
		}
		shuffle(r.begin(), r.end(), xorshift());
		for (u32 i = 0; i < N; i++) {
			T.erase(r[i]);
			S.erase(S.lower_bound(r[i]));
			T.check();
			check_compare_with_multiset(T, S);
		}
		assert(T.size() == 0);
	}
}

template<class Compare> void check_compare_with_multiset_pp1(const TreapSet<type, Compare>& T, const multiset<type, Compare>& S);
template<class Compare> void check_compare_with_multiset_pp2(const TreapSet<type, Compare>& T, const multiset<type, Compare>& S);
template<class Compare> void check_compare_with_multiset_mm1(const TreapSet<type, Compare>& T, const multiset<type, Compare>& S);
template<class Compare> void check_compare_with_multiset_mm2(const TreapSet<type, Compare>& T, const multiset<type, Compare>& S);

template<class Compare> void check_compare_with_multiset(const TreapSet<type, Compare>& T, const multiset<type, Compare>& S) {
	assert(S.size() == T.size());
	if (T.size() == 0) {
		assert(T.begin() == T.end());
		return;
	}
	check_compare_with_multiset_pp1(T, S);
	check_compare_with_multiset_pp2(T, S);
	check_compare_with_multiset_mm1(T, S);
	check_compare_with_multiset_mm2(T, S);
}

template<class Compare> void check_compare_with_multiset_pp1(const TreapSet<type, Compare>& T, const multiset<type, Compare>& S) {
	auto Ti = T.begin();
	auto Ti2 = T.begin(); Ti2++;
	auto Si = S.begin();
	assert(*Ti == *Si);
	for (; Ti2 != T.end(); ++Ti2) assert(*(++Ti) == *(++Si));
	assert(T.end() == ++Ti);
	assert(S.end() == ++Si);
}
template<class Compare> void check_compare_with_multiset_pp2(const TreapSet<type, Compare>& T, const multiset<type, Compare>& S) {
	auto Ti = T.begin();
	auto Si = S.begin();
	for (; Ti != T.end();) assert(*(Ti++) == *(Si++));
	assert(T.end() == Ti);
	assert(S.end() == Si);
}
template<class Compare> void check_compare_with_multiset_mm1(const TreapSet<type, Compare>& T, const multiset<type, Compare>& S) {
	auto Ti = T.end();
	auto Si = S.end();
	for (; Ti != T.begin();) assert(*(--Ti) == *(--Si));
	assert(S.begin() == Si);
	assert(T.begin() == Ti);
}
template<class Compare> void check_compare_with_multiset_mm2(const TreapSet<type, Compare>& T, const multiset<type, Compare>& S) {
	auto Ti = T.end(); Ti--;
	auto Si = S.end(); Si--;
	for (; Ti != T.begin();) assert(*(Ti--) == *(Si--));
	assert(S.begin() == Si);
	assert(T.begin() == Ti);
	assert(*Ti == *Si);
}

type make_random(const i64 sup_value) {
	static xorshift xor128;
	if (sup_value <= 0) return uniform_int_distribution<type>(numeric_limits<type>::min(), numeric_limits<type>::max())(xor128);
	else return uniform_int_distribution<type>(0, type(sup_value - 1))(xor128);
}

vector<type> make_random_vector(const u32 N, const i64 sup_value) {
	vector<type> res(N);
	for (u32 i = 0; i < N; i++) res[i] = make_random(sup_value);
	return res;
}