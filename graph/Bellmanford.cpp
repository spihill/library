namespace bellman_n {
#include "../snippet/Weighted12DGraph.cpp"
template<class W, class T = W>
struct Graph_B : public Graph<W> {
	vector<T> dist;
	vector<char> valid;
	Graph_B(int n) : Graph<W>(n), dist(n), valid(n) {}
};
template<class W, class T = W>
void Bellmanford(Graph_B<W, T>& G, int s, T INF_COST) {
	auto& dist = G.dist;
	auto& valid = G.valid;
	auto& e = G.e;
	auto& edges = G.edges;
	for (auto& d : dist) d = INF_COST;
	for (auto& v: valid) v = 0;
	dist[s] = 0, valid[s] = 1;
	for (int i = 0; i + 1 < G.size(); i++) {
		for (auto& x: edges) {
			if (dist[x.from] == INF_COST) continue;
			dist[x.to] = min(dist[x.to], dist[x.from] + x.w);
			valid[x.to] = true;
		}
	}
	auto valid_check = [&](auto f, int pos) {
		if (!valid[pos]) return;
		valid[pos] = false;
		for (auto& y: e[pos]) {
			f(f, y.to);
		}
	};
	for (int i = 0; i < G.size(); i++) {
		for (auto& x: e[i]) {
			if (dist[i] == INF_COST) continue;
			if (dist[x.to] > dist[i] + x.w) {
				valid_check(valid_check, x.to);
			}
		}
	}
}
}
using bellman_n::Bellmanford;
template<class T, class U = T> using graph = bellman_n::Graph_B<T, U>;