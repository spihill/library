#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja"

#include <bits/stdc++.h>

using namespace std;

namespace fibdijkstra_n {
#include "../../datastructure/FibHeap.cpp"
#include "../../for_include/has_shortest_path_graph_tag.cpp"
using u32 = uint_fast32_t;
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_shortest_path_graph_tag_v<Graph>> FibDijkstra(Graph& G, u32 start, WEIGHT INF_COST) {
	auto& e = G.e;
	for (u32 i = 0; i < G.size(); i++) {
		G.dist(i) = INF_COST;
		G.valid(i) = false;
	}
	using heap = FibHeap<pair<WEIGHT, u32>, greater<>>;
	heap q;
	vector<typename heap::np> node(G.size(), nullptr);
	q.emplace(0, start); G.dist(start) = 0;
	while (!q.empty()) {
		auto a = q.top(); q.pop();
		for (auto& p : e[a.second]) {
			if (p.weight == INF_COST) continue;
			G.valid(a.second) = 1;
			WEIGHT w = G.dist(a.second) + p.weight;
			if (w < G.dist(p.to)) {
				G.dist(p.to) = w;
				if (!node[p.to]) node[p.to] = q.emplace(w, p.to);
				q.prioritize_emplace(node[p.to], w, p.to);
			}
		}
	}
}
}
using fibdijkstra_n::FibDijkstra;

#include "../../template/ShortestPathGraph.cpp"

int main() {
	int V, E, S;
	scanf("%d%d%d", &V, &E, &S);
	auto D = make_shortest_path_graph(V);
	for (int i = 0; i < E; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		D.add_edge(a, b, c);
	}
	FibDijkstra(D, S, INT_MAX);
	for (int i = 0; i < V; i++) {
		if (D.dist(i) == INT_MAX) cout << "INF" << endl;
		else cout << D.dist(i) << endl;
	}
}