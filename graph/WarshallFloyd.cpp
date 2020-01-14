namespace warshall_floyd_n {
#include "../snippet/WeightedGraph.cpp"
template<class W, class T = W>
struct Graph_W : public Graph<W> {
	vector<vector<T>> dist;
	vector<vector<char>> valid;
	Graph_W(int n) : Graph<W>(n), dist(n, vector<T>(n)), valid(n, vector<char>(n)) {}
};

template<class W, class T>
bool WarshallFloyd(Graph_W<W, T>& G) {
	const T inf = numeric_limits<T>::max();
	const int n = G.size();
	auto& dist = G.dist;
	auto& valid = G.valid;
	auto& e = G.e;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dist[i][j] = inf;
			valid[i][j] = 0;
		}
		dist[i][i] = 0;
		valid[i][i] = 1;
	}
	for (int i = 0; i < n; i++) {
		for (auto& d : e[i]) {
			dist[i][d.to] = d.w;
			valid[i][d.to] = 1;
		}
	}
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (valid[i][k] && valid[k][j]) {
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
					valid[i][j] = 1;
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (dist[i][i] < 0) valid[i][i] = 0;
	}
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (dist[i][k] != inf && dist[k][j] != inf) valid[i][j] &= valid[i][k] & valid[k][j];
			}
		}
	}
	bool res = true;
	for (int i = 0; i < n; i++) {
		res = res && valid[i][i];
	}
	return res;
}
}
using warshall_floyd_n::WarshallFloyd;
template<class T, class U = T> using graph = warshall_floyd_n::Graph_W<T, U>;