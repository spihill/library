/**
 * @title BIT (Binary Indexed Tree)
 * @brief 0-indexed 半開区間で扱う。フェニック木 (Fenwick Tree) とも呼ばれる。
 */
template<class T>
struct BIT {
	int n;
	vector<T> bit;
	// @brief 長さ N で初期化 $O(N)$
	BIT(int n_) : n(n_), bit(n) {}
	// @brief vector で初期化 $O(N)$
	BIT(const vector<T>& v) :n(v.size()), bit(v) {
		for (int i = 0; i < n-1; i++) if ((i | (i + 1)) < n) bit[i | (i + 1)] += bit[i];
	}
	// @brief i 番目の要素に v を足す $O(\log N)$
 	// 0-indexed
	void add(int i, T v) {
		for (; i < n; i |= i + 1) bit[i] += v;
	}
	// @brief [0, i) の区間の和 の計算 $O(\log N)$
 	// 0-indexed 半開区間
	T get(int i) {
		T res = 0;
		for (i--; i >= 0; i = (i & (i + 1)) - 1) res += bit[i];
		return res;
	}
	// @brief [i, j) の区間の和 の計算 $O(\log N)$
 	// 0-indexed 半開区間
	T get(int i, int j) {
		return get(j) - get(i);
	}
};