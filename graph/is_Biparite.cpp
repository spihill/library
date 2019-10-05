struct is_Biparite : Graph {
	is_Biparite(int n) : Graph(n) {}
	vector<pair<int, int>> is_biparite() {
		vector<pair<int, int>> res;
		vector<char> color(sz, -1);
		int count[2] = {0, 0};
		auto dfs = [&] (auto f, int v, int c) {
			if (color[v] == c) return true;
			if (color[v] != -1) return false;
			color[v] = c;
			count[c]++;
			for (auto& x: e[v]) {
				if (!f(f, x.to, 1 - c)) return false;
			}
			return true;
		};
		for (int i = 0; i < sz; i++) {
			if (color[i] == -1 && !dfs(dfs, i, 0)) return vector<pair<int, int>>(0);
			if (count[0]) res.emplace_back(count[0], count[1]);
			count[0] = count[1] = 0;
		}
		return res;
	}
};
