template<class T>
map<T, int> Factorize(T n) {
	map<T, int> res;
	for (T i = 2; i * i <= n; i++) {
		while (n % i == 0) {
			res[i]++;
			n /= i;
		}
	}
	if (n != 1) res[n]++;
	return res;
}