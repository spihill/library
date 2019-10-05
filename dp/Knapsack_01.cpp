template<class T, class U>
T Knapsack_01(const T W_total, const vector<U>& value, const vector<T>& weight) {
	vector<U> dp(W_total+1);
	for (size_t i = 0; i < value.size(); i++) {
		for (T j = W_total; j >= weight[i]; j--) {
			dp[j] = max(dp[j], dp[j-weight[i]] + value[i]);
		}
	}
	return dp[W_total];a
}