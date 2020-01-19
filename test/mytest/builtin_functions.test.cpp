#define IGNORE
#include <bits/stdc++.h>
using namespace std;

#include "../../math/msb_pos.cpp"
#include "../../tools/RandomClass.cpp"

random_class rd;

template<class T>
T get_random() {
	return rd.make_random(numeric_limits<T>::min(), numeric_limits<T>::max());
}

template<class T>
void msb_check(T val, int pos) {
	if (val == 0) {
		assert(pos == -1);
		return;
	}
	using U = make_unsigned_t<T>;
	U val2 = val;
	assert(0 <= pos && pos < numeric_limits<U>::digits);
	val2 >>= pos;
	assert(val2 == 1);
}

void msb_pos_test() {
	cout << "msb_pos test" << endl;
	static_assert(msb_pos<char>(0) == -1);
	static_assert(msb_pos<int>(0) == -1);
	static_assert(msb_pos<unsigned int>(0) == -1);
	static_assert(msb_pos<long>(0) == -1);
	static_assert(msb_pos<unsigned long>(0) == -1);
	static_assert(msb_pos<long long>(0) == -1);
	static_assert(msb_pos<unsigned long long>(0) == -1);
	msb_check(1, 0);
	for (int i = 0; i < 10000000; i++) {
		auto a = get_random<char>(); msb_check(a, msb_pos(a));
		auto b = get_random<int>(); msb_check(b, msb_pos(b));
		auto c = get_random<unsigned int>(); msb_check(c, msb_pos(c));
		auto d = get_random<long long>(); msb_check(d, msb_pos(d));
		auto e = get_random<unsigned long long>(); msb_check(e, msb_pos(e));
	}
}

int main() {
	msb_pos_test();
}