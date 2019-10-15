namespace prim_n {
#include "../snippet/WeightedEdge.cpp"
template<class W>
W Prim(Edges<W>& e) {
	W res = 0;
	vector<char> used(e.size(), 0);
	priority_queue<pair<W, int>, vector<pair<W, int>>, greater<>> q;
	q.emplace(0, 0);
	while (!q.empty()) {
		auto p = q.top(); q.pop();
		if (used[p.second] != 0) continue;
		used[p.second] = 1;
		res += p.first;
		for (auto& x : e[p.second]) {
			q.emplace(x.w, x.to);
		}
	}
	return res;
}
}
using prim_n::Prim;
template<class W> using graph = prim_n::Edges<W>;