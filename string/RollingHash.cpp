template<class m1 = ModInt<1000000007>, class m2 = ModInt<1000000009>>
struct RollingHash {
	int base1;
	int base2;
	int sz;
	vector<m1> hash1;
	vector<m2> hash2;
	vector<m1> pow1;
	vector<m2> pow2;
	RollingHash(const string& s) : base1(1009), base2(1007), sz(s.length()), hash1(sz + 1, 0), hash2(sz + 1, 0), pow1(sz + 1, 1), pow2(sz + 1, 1) {
		for (int i = 0; i < sz; i++) {
			hash1[i+1] = (hash1[i] + s[i]) * base1;
			hash2[i+1] = (hash2[i] + s[i]) * base2;
			pow1[i+1] = pow1[i] * base1;
			pow2[i+1] = pow2[i] * base2;
		}
	}

	long long get(int l, int r) {
		m1 t1 = hash1[r] - hash1[l] * pow1[r - l];
		m2 t2 = hash2[r] - hash2[l] * pow2[r - l];
		return (long long) t1.x * t2.M + t2.x;
	}
};