// meguru<T>(ok, ng, isok)で呼ぶ
template<class T, class F>
T meguru(T ok, T ng, F isok) {
	static_assert(is_same<decltype(declval<F>()(declval<T>())), bool>::value, ""); 
	while (abs(ok - ng) > 1) {
		T mid = (ok + ng) / 2;
		(isok(mid) ? ok : ng) = mid;
	}
	return ok;
}