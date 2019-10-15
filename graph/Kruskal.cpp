namespace kruskal_n {
#include "../datastructure/UnionFind.cpp"
#include "../snippet/Weighted1DEdge.cpp"
template<class T>
T Kruskal(Edges<T>& e) {
	sort(e.begin(), e.end());
	UnionFind u(e.size());
	T res = 0;
	for (auto &x : e) {
		if (u.unite(x.from, x.to)) res += x.w;
	}
	return res;
}
}
using kruskal_n::Kruskal;
template<class T> using graph = kruskal_n::Edges<T>;