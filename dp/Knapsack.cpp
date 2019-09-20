template<class T, class U>
T Knapsack(const T W_total, const vector<U>& value, const vector<T>& weight) {
	vector<U> dp(W_total+1);
	for (size_t i = 0; i < value.size(); i++) {
		for (size_t j = weight[i]; j <= (size_t) W_total; j++) {
			dp[j] = max(dp[j], dp[j-weight[i]] + value[i]);
		}
	}
	return dp[W_total];
}