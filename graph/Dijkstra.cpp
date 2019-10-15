namespace dijkstra_n {
#include "../snippet/WeightedGraph.cpp"
template<class W, class T = W>
struct Graph_D : public Graph<W> {
	vector<T> dist;
	Graph_D(int n) : Graph<W>(n), dist(n) {}
};
template<class W, class T>
void Dijkstra(Graph_D<W, T>& g, int start, T INF_COST) {
	auto& dist = g.dist;
	auto& e = g.e;
	for (auto& ww : dist) ww = INF_COST;
	using Q_T = pair<T, int>;
	priority_queue<Q_T, vector<Q_T>, greater<>> q;
	q.emplace(0, start);
	while (!q.empty()) {
		auto a = q.top();
		q.pop();
		if (a.first >= dist[a.second]) continue;
		dist[a.second] = a.first;
	for (auto& p : e[a.second]) {
			if (p.w == INF_COST) continue;
			if (a.first + p.w < dist[p.to]) q.emplace(a.first + p.w, p.to);
		}
	}
}
}
using dijkstra_n::Dijkstra;
template<class T, class U = T> using graph = dijkstra_n::Graph_D<T, U>;