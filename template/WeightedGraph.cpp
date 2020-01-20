namespace weighted_graph_n{
#include "UnWeightedGraph.cpp"
template<class VertexType = long long, class WeightType = long long>
struct WeightedGraph : UnWeightedGraph<VertexType> {
	using UnWeightedGraph<VertexType>::index;
	using UnWeightedGraph<VertexType>::restore;
	using UnWeightedGraph<VertexType>::size;
	struct weighted_graph_tag {};
	vector<vector<WeightType>> weight;
	WeightedGraph(size_t N) : UnWeightedGraph<VertexType>(N), weight(N) {}
	template<class T, class U> void add_edge(T from, U to, WeightType w) {
		this->edge[index(from)].push_back(index(to));
		weight[index(from)].push_back(w);
	}
	void clear() {
		this->edge.clear();
		weight.clear();
	}
	using weight_type = WeightType;
};
template<class T = long long, class W = long long>
WeightedGraph<T, W> make_weighted_graph(size_t N) {
	return move(WeightedGraph<T, W>(N));
}
} // weighted_graph_n
template<class T, class W> using WeightedGraph = weighted_graph_n::WeightedGraph<T, W>;
using weighted_graph_n::make_weighted_graph;