namespace flow_graph_n{
#include "RevGraph.cpp"
using u32 = uint_fast32_t;
using i64 = int_fast64_t;
struct Vertex {};
template<class CAPACITY>
struct Edge {
	u32 to;
	u32 rev;
	CAPACITY capacity;
	Edge(u32 x, u32 y, CAPACITY c) : to(x), rev(y), capacity(c) {}
	Edge(u32 x, u32 y, CAPACITY c, int) : to(x), rev(y), capacity(0) {}
};
template<class CAPACITY = i64>
struct FlowGraph : RevGraph<Edge<CAPACITY>, Vertex> {
	struct flow_graph_tag {};
	FlowGraph(u32 N) : RevGraph<Edge<CAPACITY>, Vertex>(N) {}
	using CAPACITY_TYPE = CAPACITY;
};
template<class CAPACITY = i64>
FlowGraph<CAPACITY> make_flow_graph(u32 N) {
	return FlowGraph<CAPACITY>(N);
}
} // flow_graph_n
using flow_graph_n::FlowGraph;
using flow_graph_n::make_flow_graph;