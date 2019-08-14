template<class V, class E>
struct Graph {
	int sz;
	vector<V> v;
	vector<vector<E>> e;
	Graph(int n) : sz(n), v(n), e(n) {}
	template<class... Args>
	inline void assign_vertex(int pos, Args... args) {
		v[pos] = V(args...);
	}
	template<class... Args>
	inline void add_edge(int pos, Args... args) {
		e[pos].emplace_back(args...);
	}
	inline int size() {
		return sz;
	}
};
struct Vertex{};
using vertex = Vertex;
struct Edge {
	int to;
	Edge(int t) : to(t) {}
};

using edge = Edge;
using graph = Graph<vertex, edge>;

struct Centroid : public graph {
	vector<bool> dead;
	vector<int> subsize;
	vector<int> par;
	vector<vector<edge>> child_par;
	vector<vector<edge>> par_child;
	Centroid(int n) : graph(n), dead(sz, false), subsize(sz, sz), par(sz, -1), child_par(n), par_child(n) {}
	void centroid_dfs(int v, int chsize, vector<int>& res, int p = -1) {
		stack<int> s;
		stack<int> st;
		st.push(v);
		map<int, int> ok;
		par[v] = -1;
		while (!st.empty()) {
			auto t = st.top(); st.pop();
			subsize[t] = 1;
			s.push(t); 
			ok[t] = 1;
			for (auto& x: e[t]) {
				if (dead[x.to] || par[t] == x.to) continue;
				par[x.to] = t;
				st.push(x.to);
			}
		}
		while (!s.empty()) {
			auto t = s.top(); s.pop();
			if (par[t] != -1) {
				subsize[par[t]] += subsize[t];
				if (subsize[t] > chsize / 2) {
					ok[par[t]] = 0;
				}
			}
		}
		for (auto& o : ok) {
			if (o.second && (chsize + 1) / 2 <= subsize[o.first]) {
				res.push_back(o.first);
			}
		}
	}
	int centroid_build(int root = 0) {
		vector<int> next;
		int r = centroid_find(root, next);
		for (auto& x: next) {
			int t = centroid_build(x);
			par_child[r].emplace_back(t);
			child_par[t].emplace_back(r);
		}
		return r;
	}
	int centroid_find(int root, vector<int>& next_root) {
		vector<int> centroids;
		centroid_dfs(root, subsize[root], centroids);
		int centor = centroids[0];
		if (par[centor] >= 0) subsize[par[centor]] = subsize[root] - subsize[centor];
		dead[centor] = true;
		for (auto& x: e[centor]) {
			if (dead[x.to]) continue;
			next_root.emplace_back(x.to);
		}
		return centor;
	}
};
using centroid = Centroid;