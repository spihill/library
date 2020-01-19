#include "../datastructure/FibHeapMap.cpp"
namespace fibprim_n {
#include "../snippet/WeightedEdge.cpp"
template<class W>
W FibPrim(Edges<W>& e, uint_fast32_t start = 0, const W INT_COST = numeric_limits<W>::max()) {
	W res = 0;
	vector<char> used(e.size(), false);
	using heap = FibHeapMap<W, uint_fast32_t, greater<>>;
	heap q;
	vector<typename heap::np> node(e.size(), nullptr);
	q.push(0, start);
	while (!q.empty()) {
		auto p = q.top(); q.pop();
		if (used[p.second]) continue;
		used[p.second] = true;
		res += p.first;
		for (auto& x : e[p.second]) {
			if (x.w == INT_COST) continue;
			q.push(x.w, x.to);
			if (!used[x.to]) {
				if (!node[x.to]) node[x.to] = q.push(x.w, x.to);
				if (x.w < node[x.to]->get_key()) q.prioritize(node[x.to], x.w);
			}
		}
	}
	return res;
}
}
using fibprim_n::FibPrim;
template<class W> using graph = fibprim_n::Edges<W>;