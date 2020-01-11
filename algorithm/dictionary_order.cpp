#include "../datastructure/BIT.cpp"
// 辞書順で何番目かを返す。(0-indexed)
template<class T, class mint = modint>
mint dictionary_order(const vector<T>& vec) {
	size_t n = vec.size();
	if (n <= 1) return mint(0);
	vector<size_t> ord(n);
	vector<size_t> cnt(n);
	vector<size_t> cnt_sum(n+1);
	{
		map<T, size_t> ord_m;
		for (auto x : vec) ord_m[x] = 1;
		size_t index = 0;
		for (auto& p : ord_m) p.second = index++;
		for (size_t i = 0; i < n; i++) ord[i] = ord_m[vec[i]];
		for (size_t i = 0; i < n; i++) cnt[ord[i]]++;
		for (size_t i = 0; i < n; i++) cnt_sum[i+1] = cnt_sum[i] + cnt[i];
	}
	vector<mint> fact(n+1, 1);
	vector<mint> facti(n+1, 1);
	for (size_t i = 1; i <= n; i++) fact[i] = fact[i-1] * i;
	facti.back() = 1 / fact.back();
	for (size_t i = n-1; i > 0; i--) facti[i] = facti[i+1] * (i+1);
	BIT<int> bit(n+1);
	mint res = 0;
	mint inv = 1;
	for (size_t i = 0; i < n; i++) {
		inv *= facti[cnt[i]];
	}
	for (size_t i = 0; i < n-1; i++) {
		res += fact[n-i-1] * (mint(cnt_sum[ord[i]]) - bit.get(ord[i])) * inv;
		inv *= cnt[ord[i]]--;
		bit.add(ord[i], 1);
	}
	return res;
}
template<class mint = modint>
mint dictionary_order(const string& s) {
	vector<char> vs(s.begin(), s.end());
	return dictionary_order(vs);
}