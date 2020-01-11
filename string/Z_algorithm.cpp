namespace z_algorithm_n {
	using i32 = int_fast32_t;
	using u32 = uint_fast32_t;
	template<class T>
	vector<i32> Z_algorithm(const T& v) {
		const u32 n = v.size();
		vector<i32> res(n, n);
		u32 i = 1, j = 0;
		while (i < n) {
			for (;i + j < n && v[j] == v[i+j]; j++);
			res[i] = j;
			if (j == 0) {i++; continue;}
			int k;
			for (k = 1; k + res[k] < j; k++) res[i+k] = res[k];
			i += k, j -= k;
		}
		return res;
	}
} 
using namespace z_algorithm_n;