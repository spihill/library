namespace scc_n{
#include "../snippet/Graph.cpp"
template<class G>
struct SCC {
	Graph g, rg;
	vector<int> comp;
	SCC(G& g_) : g(g_.size()), rg(g_.size()), comp(g_.size()) {
		for (int i = 0; i < g_.size(); i++) {
			for (auto& x : g_.e[i]) {
				g.add_edge(i, x.to);
				rg.add_edge(x.to, i);
			}
		}
	}
	const int& operator[](int i) { return comp[i];}
	void dfs(int n, vector<char>& used, stack<int>& order) {
		if (used[n]) return;
		used[n] = true;
		for (auto x : g.e[n]) {
			dfs(x.to, used, order);
		}
		order.emplace(n);
	}
	void rdfs(int n, vector<int>& comp, int group) {
		if (comp[n] != -1) return;
		comp[n] = group;
		for (auto x : rg.e[n]) rdfs(x.to, comp, group);
	}
	Graph build() {
		const size_t n = g.size();
		stack<int> order;
		vector<char> used(n, 0);
		for (size_t i = 0; i < n; i++) dfs(i, used, order);

		comp = vector<int>(n, -1);
		int group = 0;
		while (order.size()) {
			int i = order.top(); order.pop();
			if (comp[i] == -1) rdfs(i, comp, group++);
		}
		Graph res(group);
		for (size_t i = 0; i < n; i++) {
			for (auto& x : g.e[i]) {
				int s = comp[i], t = comp[x.to];
				if (s == t) continue;
				res.add_edge(s, t);
			}
		}
		return res;
	}
};
} // scc_n
using graph = scc_n::Graph;
template<class G>
using SCC = scc_n::SCC<G>;