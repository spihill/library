template<class T>
struct SWAG {
	struct node {
		T val, sum;
		node() : val(), sum() {}
		node(T v, T s) : val(v), sum(s) {}
	};
	stack<node> F, B;
	T fold_all() const {
		if (empty()) return T();
		if (F.empty()) return B.top().sum;
		if (B.empty()) return F.top().sum;
		return F.top().sum + B.top().sum;
	}
	void push(T x) {
		if (B.empty()) B.emplace(x, x);
		else {
			T s{B.top().sum + x};
			B.emplace(x, move(s));
		}
	}
	void pop() {
		assert(!empty());
		if (F.empty()) {
			F.emplace(B.top().val, B.top().val); B.pop();
			while (B.size()) {
				F.emplace(B.top().val, B.top().val + F.top().sum);
				B.pop();
			}
		}
		F.pop();
	}
	bool empty() const {
		return size() == 0;
	}
	uint_fast32_t size() const {
		return F.size() + B.size();
	}
};

template<class T>
struct monoid {
	// const static T UNITY = 0;
	// monoid operator+(const monoid& rhs) const noexcept {return monoid(this->val + rhs.val);}
	monoid() : val(UNITY) {}
	explicit monoid(T x) : val(x) {}
	T val;
	bool operator<(const monoid& rhs) const noexcept {return val < rhs.val;}
	bool operator>(const monoid& rhs) const noexcept {return rhs < *this;}
	bool operator<=(const monoid& rhs) const noexcept {return !(rhs < *this);}
	bool operator>=(const monoid& rhs) const noexcept {return !(*this < rhs);}
	bool operator==(const monoid& rhs) const noexcept {return !(*this < rhs) && !(rhs < *this);}
	bool operator!=(const monoid& rhs) const noexcept {return *this < rhs || rhs < *this;}
	friend istream& operator>>(istream& lhs, monoid& rhs) {
		lhs >> rhs.val;
		return lhs;
	}
	friend ostream& operator<<(ostream& lhs, monoid& rhs) {
		lhs << rhs.val;
		return lhs;
	}
};
// using mono = monoid<long long>;

vector<int> syakutori(const vector<mono>& v, const function<bool(mono)>& f) {
	SWAG<mono> S;
	int l = 0, r = 0;
	const int N = v.size();
	vector<int> res(N);
	while (l < N) {
		while (r < N && f((S.fold_all() + v[r]).val)) S.push(v[r++]);
		res[l] = r;
		l++;
		if (r < l) r++;
		else S.pop();
	}
	return move(res);
}