// meguru<T>(ok, ng, isok)で呼ぶ
template<class T>
T meguru(T ok, T ng, function<bool(T)> isok) {
	while (abs(ok - ng) > 1) {
		T mid = (ok + ng) >> 1;
		(isok(mid) ? ok : ng) = mid;
	}
	return ok;
}