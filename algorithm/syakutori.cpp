#include "../datastructure/SWAG.cpp"
#include "../math/monoid_t.cpp"
// v : 対象の列 (型が monoid_type を持つ必要がある)
// f : 区間が満たすべき条件を表す関数 (引数 : T::monoid_type 戻り値 : bool)
// continue_flag (default : true) : f の戻り値が continue_flag と等しいような区間を列挙
// 戻り値 : ret[l] = r; (条件を満たす区間 [l, i) の中で最大の i が r)
template<class T>
vector<int> syakutori(const vector<T>& v, const function<bool(monoid_t<T>)>& f, bool continue_flag = true) {
	SWAG<T> S;
	int l = 0, r = 0;
	const int N = v.size();
	vector<int> res(N);
	if (continue_flag) {
		while (l < N) {
			while (r < N && f((T(S.fold_all()) + v[r]).val)) S.push(v[r++]);
			 res[l++] = r;
			if (r < l) r++;
			else S.pop();
		}
	} else {
		while (l < N) {
			while (r < N && !f(S.fold_all())) S.push(v[r++]);
			if (r == N && !f(S.fold_all())) {
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