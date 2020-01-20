/** 
 * @title Union Find Tree
 * @brief 初期化以外の各操作がほぼ$O(1)$で完了すると思ってよい。 0-indexed
 */
struct UnionFind {
	vector<int> par;
	UnionFind(int a) : par(a, -1) {}
// 頂点 x の親を返す
	int root(int x) { return par[x] < 0 ? x : par[x] = root(par[x]);}
// @brief 頂点 x と 頂点 y が連結されているか
	bool same(int x, int y) { return root(x) == root(y);}
// @brief 頂点 x と 頂点 y を連結する。すでに連結していたら false
	bool unite(int x, int y) {
		x = root(x);
		y = root(y);
		if (x == y) return false;
		if (size(x) < size(y)) swap(x, y);
		par[x] += par[y];
		par[y] = x;
		return true;
	}
// @brief 頂点 x が所属しているグループのサイズを返す
	int size(int x) { return -par[root(x)];}
};
