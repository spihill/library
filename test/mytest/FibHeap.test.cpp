#include <bits/stdc++.h>

using namespace std;

#include "../../datastructure/FibHeap.cpp"

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
vector<type> make_random_vector(const u32 N, const i64 sup_value);
type make_random(const i64 sup_value);
template<class Compare> void compare_with_pqueue(const FibHeap<type, Compare>& F, const priority_queue<type, vector<type>, Compare>& Q);

int main() {
	check_small_size_queries(300, 100, less<type>(), 20);
	check_small_size_queries(300, 100, less<type>());
	check_small_size_queries(300, 100, greater<type>(), 20);
	check_small_size_queries(300, 100, greater<type>());
}

template<class Compare> void check_small_size_queries(const u32 N, const u32 Q, Compare C, const i64 sup_value) {
	FibHeap<type, Compare> F;
	for (u32 cnt = 0; cnt < Q; cnt++) {
		vector<type> r = make_random_vector(N, sup_value);
		priority_queue<type, vector<type>, Compare> Q;
		vector<int> query;
		{
			u32 in = N, out = N;
			for (u32 i = 0; i < 2 * N; i++) {
				if (in == out || make_random(in + out) < in) {
					in--;
					query.push_back(1);
				} else {
					query.push_back(0);
					out--;
				}
			}
		}
		for (u32 i = 0, in = 0; i < 2*N; i++) {
			compare_with_pqueue(F, Q);
			if (F.size()) assert(F.top() == Q.top());
			if (query[i]) {
				Q.push(r[in]);
				F.push(r[in++]);
			} else {
				Q.pop();
				F.pop();
			}
		}
		compare_with_pqueue(F, Q);
		assert(F.size() == 0);
	}
}

template<class Compare> void compare_with_pqueue(const FibHeap<type, Compare>& F, const priority_queue<type, vector<type>, Compare>& Q) {
	assert(F.size() == Q.size());
	if (F.size()) assert(F.top() == Q.top());
	F.check();
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