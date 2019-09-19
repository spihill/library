template<class T>
struct BIT {
	int n;
	vector<T> bit;
	BIT(int n_) : n(n_), bit(n) {}
	void add(int x, T v) {
		for (int i = x+1; i <= n; i += i & -i) {
			bit[i] += v;
		}
	}
	T get(int x) {
		T res = 0;
		for (int i = x+1; i; i -= i & -i) {
			res += bit[i];
		}
		return res;
	}
};
