template<class T>
void Factorize(T n, map<T, int>& res) {
	for (T i = 2; i * i <= n; i++) {
		while (n % i == 0) {
			res[i]++;
			n /= i;
		}
	}
	if (n != 1) res[n]++;
}
template<class T>
void Factorize(T n, vector<int>& res) {
	for (T i = 2; i * i <= n; i++) {
		while (n % i == 0) {
			res.push_back(i);
			n /= i;
		}
	}
	if (n != 1) res.push_back(n);
}