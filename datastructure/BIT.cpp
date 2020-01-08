template<class T>
struct BIT {
	int n;
	vector<T> bit;
	BIT(int n_) : n(n_), bit(n) {}
	BIT(const vector<T>& v) : BIT(v.size()) {
		for (int i = 0; i < n; i++) bit[i] = v[i];
		for (int i = 0; i < n-1; i++) if ((i | (i + 1)) < n) bit[i | (i + 1)] += bit[i];
	}
	// bit[i] += v
	void add(int i, T v) {
		for (; i < n; i |= i + 1) bit[i] += v;
	}
	// sum of [0, i)
	T get(int i) {
		T res = 0;
		for (i--; i >= 0; i = (i & (i + 1)) - 1) res += bit[i];
		return res;
	}
	// sum of [i, j)
	T get(int i, int j) {
		return get(j) - get(i);
	}
};