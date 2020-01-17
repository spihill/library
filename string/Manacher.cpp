template<class T>
vector<int> manacher(const vector<T>& s) {
	const int n = s.size();
	vector<int> res(n);
	int pos = 0, len = 0;
	while (pos < n) {
		while (pos - len >= 0 && pos + len < n && s[pos - len] == s[pos + len]) len++;
		res[pos] = len;
		int i;
		for (i = 1; pos - i >= 0 && pos + i < n && i + res[pos-i] < len; i++) res[pos+i] = res[pos-i];
		pos += i; len -= i;
	}
	return res;
}
vector<int> manacher(const string& s) {
	return manacher(vector<char>(s.begin(), s.end()));
}