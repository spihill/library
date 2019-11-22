#include "../datastructure/FibHeapMap.cpp"
namespace fibdijkstra_n {
#include "../snippet/WeightedGraph.cpp"
template<class W, class T = W>
struct Graph_D : public Graph<W> {
	vector<T> dist;
	Graph_D(int n) : Graph<W>(n), dist(n) {}
};
template<class W, class T>
void FibDijkstra(Graph_D<W, T>& g, int start, T INF_COST) {
	auto& dist = g.dist;
	auto& e = g.e;
	for (auto& ww : dist) ww = INF_COST;
	using heap = FibHeapMap<T, uint_fast32_t, greater<>>;
	heap q;
	vector<typename heap::np> node(g.size(), nullptr);
	q.push(0, start); dist[start] = 0;
	while (!q.empty()) {
		auto a = q.top(); q.pop();
		for (auto& p : e[a.second]) {
			if (p.w == INF_COST) continue;
			W w = dist[a.second] + p.w;
			if (w < dist[p.to]) {
				dist[p.to] = w;
				if (!node[p.to]) node[p.to] = q.push(w, p.to);
				q.increase_key(node[p.to], w);
			}
		}
	}
}
}
using fibdijkstra_n::FibDijkstra;
template<class T, class U = T> using graph = fibdijkstra_n::Graph_D<T, U>;