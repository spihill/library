
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_E"

#include<bits/stdc++.h>

using namespace std;

#include "../../dp/Levenshtein.cpp"

int main() {
	string a, b;
	cin >> a >> b;
	cout << Levenshtein(a, b) << endl;
}