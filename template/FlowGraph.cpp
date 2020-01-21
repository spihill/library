namespace flow_graph_n{
#include "UnWeightedGraph.cpp"
template<class VertexType = long long, class CapacityType = long long>
struct FlowGraph : UnWeightedGraph<VertexType> {
	using UnWeightedGraph<VertexType>::index;
	using UnWeightedGraph<VertexType>::restore;
	using UnWeightedGraph<VertexType>::size;
	struct flow_graph_tag {};
	vector<vector<CapacityType>> capacity;
	vector<vector<size_t>> revedge;
	FlowGraph(size_t N) : UnWeightedGraph<VertexType>(N), capacity(N), revedge(N) {}
	template<class T, class U> void add_edge(T from, U to, CapacityType c) {
		this->edge[index(from)].push_back(index(to));
		capacity[index(from)].push_back(c);
		revedge[index(from)].push_back(this->edge[index(to)].size());

		this->edge[index(to)].push_back(index(from));
		capacity[index(to)].push_back(CapacityType());
		revedge[index(to)].push_back(this->edge[index(from)].size()-1);
	}
	void clear() {
		this->edge.clear();
		capacity.clear();
		revedge.clear();
	}
	using capacity_type = CapacityType;
};
template<class V = long long, class C = long long>
FlowGraph<V, C> make_flow_graph(size_t N) {
	return move(FlowGraph<V, C>(N));
}
} // weighted_graph_n
template<class V, class C> using FlowGraph = flow_graph_n::FlowGraph<V, C>;
using flow_graph_n::make_flow_graph;