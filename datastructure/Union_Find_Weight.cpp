template<class Abel> struct Union_Find_Weight
{
	vector<int> par;
	vector<Abel> diff_weight;
	int n;
	Union_Find_Weight(int a, Abel SUM_UNITY = 0) {init(a, SUM_UNITY);}
	void init(int a, Abel SUM_UNITY) {
		n = a;
		par.resize(n, -1);
		diff_weight.resize(n, SUM_UNITY);
	}
	int root(int x) {
		if (par[x] < 0) return x;
		int r = root(par[x]);
		diff_weight[x] += diff_weight[par[x]];
		return par[x] = r;
	}
	Abel weight(int x) {
		root(x);
		return diff_weight[x];
	}
	Abel diff(int x, int y) {
		return weight(y) - weight(x);
	}
	bool same(int x, int y) {
		return root(x) == root(y);
	}
// weight(y) - weight(x) = w
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
	int size(int x) {
		x = root(x);
		return -par[x];
	}
};
