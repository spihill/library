/**
 * @title２次元 BIT
 * @brief 0-indexed 半開区間で扱う (Binary Indexed Tree)
 */
template<class T>
struct BIT_2D {
	int H, W;
	vector<vector<T>> bit;
	// @brief 大きさ H * W で初期化 $O(H * W)$
	BIT_2D(int h, int w) : H(h), W(w), bit(H, vector<T>(W)) { }
	// @brief 2次元 vector で初期化 $O(H * W)$
	BIT_2D(vector<vector<T>>& v) : bit(v) {
		assert(v.size());
		assert(v[0].size());
		H = v.size();
		W = v[0].size();
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W-1; j++) {
				if ((j | (j + 1)) < W) bit[i][j | (j + 1)] += bit[i][j];
			}
		}
		for (int i = 0; i < H-1; i++) {
			if ((i | (i + 1)) >= H) continue;
			for (int j = 0; j < W; j++) {
				bit[i | (i + 1)][j] += bit[i][j];
			}
		}
	}
	// @brief (r, c) に v を 足す $O(\log H * \log W)$
 	// 0-indexed
	void add(int r, int c, T v) {
		for (int i = r; i < H; i |= i + 1) {
			for (int j = c; j < W; j |= j + 1) {
				bit[i][j] += v;
			}
		}
	}
	// @brief (0, 0) ～ (r-1, c-1) の 長方形部分の sum を計算する $O(\log H * \log W)$
 	// 0-indexed 半開区間
	T get(int r, int c) {
		T res = 0;
		for (int i = r; i >= 0; i = (i & (i + 1)) - 1) {
			for (int j = c; j >= 0; j = (j & (j + 1)) - 1) {
				res += bit[i][j];
			}
		}
		return res;
	}
	// @brief (r1, c1) ～ (r2 - 1, c2 - 1) の 長方形部分の sum を計算する $O(\log H * \log W)$
 	// 0-indexed 半開区間
	T get_sum(int r1, int c1, int r2, int c2) {
		r1--; c1--; r2--; c2--;
		return get(r2, c2) - get(r1, c2) - get(r2, c1) + get(r1, c1);
	}
};