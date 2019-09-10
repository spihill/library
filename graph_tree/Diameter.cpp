template<class T>
struct Graph
{
	struct Vertex{};
	struct Edge {
		int to;
		int cost;
		Edge(int t, int c) : to(t), cost(c) {}
		Edge() {}
	};
	int sz;
	vector<Vertex> v;
	vector<vector<Edge>> e;
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
template<class T>
struct Diameter : public Graph<T> {
	Diameter(int n) : Graph<T>(n) {}
	int Diameter_solve() {
		auto dfs = [this](auto f, int start, int& goal, int par = -1) -> int {
			goal = start;
			int res = 0;
			for (auto& i: this->e[start]) {
				if (i.to == par) continue;
				int t;
				int r = f(f, i.to, t, start);
				r += i.cost;
				if (r > res) {
					res = r;
					goal = t;
				}
			}
			return res;
		};
		int g;
		dfs(dfs, 0, g);
		return dfs(dfs, g, g);
	}
};
