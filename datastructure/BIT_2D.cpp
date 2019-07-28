template<class T>
struct BIT_2D {
	int R, C;
	vector<vector<T>> bit;
	BIT_2D(int r, int c) {
		R = r;
		C = c;
		bit.resize(r+1, vector<T>(c+1, 0));
	}
	void add(int r, int c, T v) {
		for (int i = r+1; i <= R; i += i & -i) {
			for (int j = c+1; j <= C; j += j & -j) {
				bit[i][j] += v;
			}
		}
	}
	T get(int r, int c) {
		T res = 0;
		for (int i = r+1; i; i -= i & -i) {
			for (int j = c+1; j; j -= j & -j) {
				res += bit[i][j];
			}
		}
		return res;
	}
// bit[r1][c1] ~~ bit[r2 - 1][c2 - 1]
	T get_sum(int r1, int c1, int r2, int c2) {
		r1--; c1--; r2--; c2--;
		return get(r2, c2) - get(r1, c2) - get(r2, c1) + get(r1, c1);
	}
};