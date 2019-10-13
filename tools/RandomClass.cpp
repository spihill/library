template<class T>
struct RandomClass {
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
	RandomClass() : rd(), xor128(rd()) {}
	T make_random(T min_v, T max_v) { 
		static_assert(is_integral<T>::value);
		return uniform_int_distribution<T>(min_v, max_v)(xor128);
	}
};
#define make_real(type) template<> type RandomClass<type>::make_random(type min_v, type max_v) { return uniform_real_distribution<type>(min_v, max_v)(xor128);}
make_real(float)
make_real(double)
make_real(long double)
#undef make_real