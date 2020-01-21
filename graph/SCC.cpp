namespace scc_n{
#include "../template/UnWeightedGraph.cpp"
#include "../for_include/has_graph_tag.cpp"
template<class T> using super_graph = UnWeightedGraph<T>;
template<class T>
struct SCC : super_graph<T> {
	using super_graph<T>::index;
	using graph = UnWeightedGraph<long long>;
	vector<vector<T>> redge;
	vector<int> comp;
	SCC(size_t N) : super_graph<T>(N), redge(N), comp(N) {}
	template<class Graph>
	SCC(Graph& g_) : SCC(g_.size()) {
		static_assert(has_graph_tag_v<Graph>);
		construct_graph(g_);
	}
	template<class X, class Y> void add_edge(X from, Y to) {
		this->edge[index(from)].push_back(index(to));
		redge[index(to)].push_back(index(from));
	}
	const int& operator[](int i) { return comp[i];}
	void dfs(int n, vector<char>& used, stack<int>& order) {
		if (used[n]) return;
		used[n] = true;
		for (auto x : this->edge[n]) {
			dfs(x, used, order);
		}
		order.emplace(n);
	}
	void rdfs(int n, vector<int>& comp, int group) {
		if (comp[n] != -1) return;
		comp[n] = group;
		for (auto x : redge[n]) rdfs(x, comp, group);
	}
	graph build() {
		const size_t n = this->edge.size();
		stack<int> order;
		vector<char> used(n, 0);
		for (size_t i = 0; i < n; i++) dfs(i, used, order);

		comp = vector<int>(n, -1);
		int group = 0;
		while (order.size()) {
			int i = order.top(); order.pop();
			if (comp[i] == -1) rdfs(i, comp, group++);
		}

		graph res(group);
		for (size_t i = 0; i < n; i++) {
			for (auto& x : this->edge[i]) {
				int s = comp[i], t = comp[x];
				if (s == t) continue;
				res.add_edge(s, t);
			}
		}
		return res;
	}
private:
	template<class Graph>
	void construct_graph(const Graph& G) {
		for (size_t i = 0; i < G.size(); i++) {
			for (auto& x : G.edge[i]) {
				this->edge[i].push_back(x);
				redge[x].push_back(i);
			}
		}
	}
};
template<class T> using graph = SCC<T>;
template<class T = long long>
graph<T> make_scc(size_t N) {
	return move(graph<T>(N));
}
} // scc_n
using scc_n::make_scc;
using scc_n::SCC;