namespace shortest_path_graph_n {
#include "WeightedGraph.cpp"
template<class VertexType = long long, class WeightType = long long>
struct ShortestPathGraph : WeightedGraph<VertexType, WeightType> {
	using WeightedGraph<VertexType, WeightType>::index;
	using WeightedGraph<VertexType, WeightType>::restore;
	using WeightedGraph<VertexType, WeightType>::size;
	struct shortest_path_graph_tag {};
	vector<WeightType> dist;
	vector<char> valid;
	ShortestPathGraph(size_t N) : WeightedGraph<VertexType, WeightType>(N), dist(N), valid(N) {}
};
template<class T = long long, class W = long long>
ShortestPathGraph<T, W> make_shortest_path_graph(size_t N) {
	return move(ShortestPathGraph<T, W>(N));
}
} // shortest_path_graph_n
template<class T, class W> using ShortestPathGraph = shortest_path_graph_n::ShortestPathGraph<T, W>;
using shortest_path_graph_n::make_shortest_path_graph;