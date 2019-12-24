#include "../datastructure/SWAG.cpp"
template<class T>
vector<int> syakutori(const vector<T>& v, const function<bool(typename T::monoid_type)>& f, bool continue_flag = true) {
	SWAG<T> S;
	int l = 0, r = 0;
	const int N = v.size();
	vector<int> res(N);
	if (continue_flag) {
		while (l < N) {
			while (r < N && f((S.fold_all() + v[r]).val)) S.push(v[r++]);
			 res[l++] = r;
			if (r < l) r++;
			else S.pop();
		}
	} else {
		while (l < N) {
			while (r < N && !f(S.fold_all().val)) S.push(v[r++]);
			if (r == N && !f(S.fold_all().val)) {
				for (; l < N; l++) res[l] = N + 1;
				break;
			}
			res[l++] = r;
			if (r < l) r++;
			else S.pop();
		}
	}
	return move(res);
}