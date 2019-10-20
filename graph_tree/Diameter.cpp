namespace diameter_n {
#include "../snippet/WeightedEdge.cpp"
template<class W>
int Diameter(Edges<W>& e) {
	auto dfs = [&](auto f, int start, int& goal, int par = -1) -> W {
		goal = start;
		W res = 0;
		for (auto& i: e[start]) {
			if (i.to == par) continue;
			int t;
			W r = f(f, i.to, t, start);
			r += i.w;
			if (r > res) {
				res = r;
				goal = t;
			}
		}
		return res;
	};
	int g;
	dfs(dfs, 0, g);
	return dfs(dfs, g, g);
}
}
template<class W> using graph = diameter_n::Edges<W>;
using diameter_n::Diameter;