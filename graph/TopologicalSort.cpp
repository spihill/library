namespace topological_sort_n {
#include "../snippet/Edge.cpp"
pair<bool, vector<int>> TopologicalSort(Edges& e) {
	int V = e.size();
	vector<char> visited(V, 0);
	vector<int> cnt(V, 0);
	for (int i = 0; i < V; i++) {
		for (auto& x : e[i]) {
			cnt[x.to]++;
		}
	}
	stack<int> s;
	vector<int> res;
	for (int i = 0; i < V; i++) {
		if (cnt[i] == 0) s.push(i);
	}
	while (!s.empty()) {
		int v = s.top(); s.pop();
		res.push_back(v);
		for (auto& x : e[v]) {
			if (--cnt[x.to] == 0) s.push(x.to);
		}
	}
	return make_pair((int)res.size() == V, res);
}
}
using graph = topological_sort_n::Edges;
using topological_sort_n::TopologicalSort;