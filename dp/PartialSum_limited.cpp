vector<int> PartialSum_limited(const vector<int>& w, const vector<int>& c, int w_max) {
	assert(w.size() == c.size());
	vector<int> dp(w_max + 1, -1);
	dp[0] = 0;
	for (int i = 0; i < (int) w.size(); i++) {
		for (int j = 0; j < (int) dp.size(); j++) {
			if (w[i] >= 0) {
				if (dp[j] >= 0) {
					dp[j] = c[i];
				} else if (j < w[i] || dp[j-w[i]] <= 0) {
					dp[j] = -1;
				} else {
					dp[j] = dp[j-w[i]] - 1;
				}
			}
		}
	}
	return dp;
}