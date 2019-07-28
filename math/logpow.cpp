template<class T>
T logpow(T x, long long p)
{
	if (p == 0) {
		return 1;
	}
	if (p % 2) {
		return x * logpow(x, p-1);
	}
	T t = logpow(x, p/2);
	return t * t;
}
