template<class EDGE, class VERTEX>
struct RevEdgeGraph {
	using u32 = uint_fast32_t;
	using u64 = uint_fast64_t;
	struct graph_tag {};
	struct revedge_graph_tag {};
	const u32 n;
	vector<vector<EDGE>> e;
	vector<vector<EDGE>> re;
	vector<VERTEX> v;
	vector<u64> idx;
	vector<u64> ridx;
	RevEdgeGraph(u32 N) : n(N), e(n), re(n), v(n) {}
	template<class...  Args> void add_edge(u32 from, u32 to, Args... args) {
		idx.push_back((static_cast<u64>(from) << 32) | e[from].size());
		e[from].emplace_back(to, args...);
		idx.push_back((static_cast<u64>(from) << 32) | re[to].size());
		re[to].emplace_back(from, args...);
	}
	u32 size() const {return n;}
	using EDGE_TYPE = EDGE;
	using VERTEX_TYPE = VERTEX;
};