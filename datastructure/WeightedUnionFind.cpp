/** 
 * @title ポテンシャル付き Union Find Tree
 * @brief 初期化以外の各操作がほぼ$O(1)$で完了すると思ってよい。 0-indexed
 */
template<class Abel>
struct WeightedUnionFind {
	vector<int> par;
	vector<Abel> diff_weight;
	WeightedUnionFind(int N, Abel SUM_UNITY = 0) : par(N, -1), diff_weight(N, SUM_UNITY) {}
// 頂点 x の親を返す
	int root(int x) {
		if (par[x] < 0) return x;
		int r = root(par[x]);
		diff_weight[x] += diff_weight[par[x]];
		return par[x] = r;
	}
// @brief 頂点 x のポテンシャル を返す
	Abel weight(int x) {
		root(x);
		return diff_weight[x];
	}
// @brief weight(y) - weight(x) を返す
	Abel diff(int x, int y) {
		return weight(y) - weight(x);
	}
// @brief 頂点 x と 頂点 y が連結されているか
	bool same(int x, int y) {
		return root(x) == root(y);
	}
// @brief weight(y) - weight(x) = w となるように連結する。連結されなかったら false
	bool unite(int x, int y, Abel w) {
		w += weight(x);
		w -= weight(y);
		x = root(x);
		y = root(y);
		if (x == y) return false;
		if (size(x) < size(y)) swap(x, y), w = -w;
		par[x] += par[y];
		par[y] = x;
		diff_weight[y] = w;
		return true;
	}
// @brief 頂点 x が所属しているグループのサイズを返す
	int size(int x) {
		x = root(x);
		return -par[x];
	}
};
