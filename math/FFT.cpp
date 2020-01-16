// @title 高速フーリエ変換
template<class T=complex<double>>
struct FFT {
	vector<vector<T>> power;
	FFT(int N) {
		int x = 1, B = 1;
		while (x < N) x <<= 1, B++;
		power.resize(B+1);
		for (int i = 0; i < B+1; i++) {
			int sz = 1 << i;
			power[i].resize(sz);
			for (int j = 0; j < sz; j++) power[i][j] = polar(1.0, 2*M_PI*j/sz);
		}
	}
	void DFT(typename vector<T>::iterator F, typename vector<T>::iterator t, int p) {
		if (p == 0) return;
		const int n = power[p].size();
		const int half = power[p-1].size();
		for (int i = 0; i < half; i++) {
			t[i] = F[2*i]; t[i+half] = F[2*i+1];
		}
		DFT(t, F, p-1); DFT(t+half, F, p-1);
		for (int i = 0; i < half; i++) {
			F[i] = t[i] + power[p][i] * t[i+half];
		}
		for (int i = half, j = 0; i < n; i++, j++) {
			F[i] = t[j] + power[p][i] * t[j+half];
		}
	}
	template<class U>
	vector<U> convolution(const vector<U>& f, const vector<U>& g) {
		int n = f.size() + g.size() - 1;
		int sz = 1;
		int p = 0;
		while (sz < n) sz <<= 1, p++;
		vector<T> cf(f.begin(), f.end());
		vector<T> cg(g.begin(), g.end());
		cf.resize(sz);
		cg.resize(sz);
		vector<T> tmp(sz);
		DFT(cf.begin(), tmp.begin(), p);
		DFT(cg.begin(), tmp.begin(), p);
		for (int i = 0; i < sz; i++) cf[i] = conj(cf[i] * cg[i]) / (double) sz;
		DFT(cf.begin(), tmp.begin(), p);
		vector<U> res(sz);
		for (int i = 0; i < sz; i++) res[i] = (int) (cf[i].real() + 0.5);
		return res;
	}
};