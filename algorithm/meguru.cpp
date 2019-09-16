// meguru<T>(ok, ng, isok)で呼ぶ
template<class T>
T meguru(T ok, T ng, function<bool(T)> isok) {
	while (abs(ok - ng) > 1) {
		T mid = (ok + ng) / 2;
		if (isok(mid)) ok = mid;
		else ng = mid;
	}
	return ok;
}