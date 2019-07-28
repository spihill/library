template<class T>
struct ModComb {
	vector<T> fact;
	vector<T> facti;
	ModComb(int n) : fact(n+1), facti(n+1) {
		fact[0] = 1;
		for (int i = 1; i < n + 1; i++) {
			fact[i] = fact[i-1] * i;
		}
		facti[n] = 1 / fact[n];
		for (int i = n-1; i >= 0; i--) {
			facti[i] = facti[i+1] * (i + 1);
		}
	}
	T C(int n, int r) const {
		if(n < 0 || r < 0 || n < r) return 0;
		return fact[n] * facti[r] * facti[n-r];
	}
	T P(int n, int r) const {
		if(n < 0 || r < 0 || n < r) return 0;
		return fact[n] * facti[n-r];
	}
	T H(int n, int r) const {
		if(n < 0 || r < 0) return 0;
		return C(n + r - 1, r);
	}
};
using modcomb = ModComb<modint>;