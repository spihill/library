template<class T>
int LCS(const T& a, const T& b) {
	vector<vector<int>> dp(a.size() + 1, vector<int>(b.size() + 1));
	for (size_t i = 0; i < a.size(); i++) {
		for (size_t j = 0; j < b.size(); j++) {
			int& r = dp[i+1][j+1];
			r = max(dp[i][j+1], dp[i+1][j]);
			if (a[i] == b[j]) r = max(r, dp[i][j] + 1);
		}
	}
	return dp[a.size()][b.size()];
}