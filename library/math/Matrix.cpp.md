---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: 行列

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/Matrix.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-17 01:32:20+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/Matrix.test.cpp.html">test/aoj/Matrix.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// @title 行列
template <class T>
struct Matrix {
	int row;
	int column;
	vector<vector<T>> v;
	vector<T> &operator[](int i) { return (v[i]); }
	Matrix(int i, int j) {init(i, j);}
	Matrix() : Matrix(0, 0) {}
	void init(int i, int j) {
		row = i;
		column = j;
		v.resize(i, vector<T>(j, 0));
	}
	Matrix(const Matrix &cp) {
		row = cp.row;
		column = cp.column;
		v = cp.v;
	}
	~Matrix() {}
	Matrix operator=(const Matrix &a) {
		row = a.row;
		column = a.column;
		v = a.v;
		return (*this);
	}
	Matrix operator+(const Matrix &a) {
		Matrix r(row, column);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				r.v[i][j] = v[i][j] + a.v[i][j];
			}
		}
		return (r);
	}
	Matrix operator-(const Matrix &a) {
		Matrix r(row, column);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				r.v[i][j] = v[i][j] - a.v[i][j];
			}
		}
		return (r);
	}
	Matrix operator*(const Matrix &a)
	{
		Matrix r(row, a.column);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < a.column; j++) {
				for (int k = 0; k < column; k++) {
					r.v[i][j] += v[i][k] * a.v[k][j];
				}
			}
		}
		return (r);
	}
	Matrix operator*(const int b) {
		Matrix r(row, column);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				r.v[i][j] = b * v[i][j];
			}
		}
		return (r);
	}
	Matrix operator+(const int b) {
		Matrix r(row, column);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				r.v[i][j] = b + v[i][j];
			}
		}
		return (r);
	}
	Matrix operator-(const int b) {
		Matrix r(row, column);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				r.v[i][j] = v[i][j] - b;
			}
		}
		return (r);
	}
	void unit_matrix() {
		int n = row;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				v[i][j] = (i == j);
			}
		}
	}
	Matrix<T> accumu_sum() {
		Matrix<T> r(row+1, column+1);
		for (int i = 1; i <= row; i++) {
			for (int j = 1; j <= column; j++) {
				r[i][j] = v[i-1][j-1] + r[i-1][j] + r[i][j-1] - r[i-1][j-1];
			}
		}
		return (r);
	}
	//半開区間で指定
	T get_sum_accumu(int r1, int c1, int r2, int c2) {
		return v[r2][c2] + v[r1][c1] - v[r2][c1] - v[r1][c2];
	}
	Matrix transposed() {
		Matrix t(column, row);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				t[j][i] = v[i][j];
			}
		}
		return (t);
	}
	friend ostream &operator<<(ostream &lhs, const Matrix<T> &rhs) {
		for (int i = 0; i < rhs.row; i++) {
			for (int j = 0; j < rhs.column - 1; j++) {
				lhs << rhs.v[i][j] << " ";
			}
			lhs << rhs.v[i][rhs.column - 1];
			if (i != rhs.row-1) cout << endl;
		}
		return lhs;
	}
	friend istream &operator>>(istream &lhs, Matrix<T> &rhs) {
		for (int i = 0; i < rhs.row; i++) {
			for (int j = 0; j < rhs.column; j++) {
				lhs >> rhs.v[i][j];
			}
		}
		return lhs;
	}
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/Matrix.cpp"
// @title 行列
template <class T>
struct Matrix {
	int row;
	int column;
	vector<vector<T>> v;
	vector<T> &operator[](int i) { return (v[i]); }
	Matrix(int i, int j) {init(i, j);}
	Matrix() : Matrix(0, 0) {}
	void init(int i, int j) {
		row = i;
		column = j;
		v.resize(i, vector<T>(j, 0));
	}
	Matrix(const Matrix &cp) {
		row = cp.row;
		column = cp.column;
		v = cp.v;
	}
	~Matrix() {}
	Matrix operator=(const Matrix &a) {
		row = a.row;
		column = a.column;
		v = a.v;
		return (*this);
	}
	Matrix operator+(const Matrix &a) {
		Matrix r(row, column);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				r.v[i][j] = v[i][j] + a.v[i][j];
			}
		}
		return (r);
	}
	Matrix operator-(const Matrix &a) {
		Matrix r(row, column);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				r.v[i][j] = v[i][j] - a.v[i][j];
			}
		}
		return (r);
	}
	Matrix operator*(const Matrix &a)
	{
		Matrix r(row, a.column);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < a.column; j++) {
				for (int k = 0; k < column; k++) {
					r.v[i][j] += v[i][k] * a.v[k][j];
				}
			}
		}
		return (r);
	}
	Matrix operator*(const int b) {
		Matrix r(row, column);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				r.v[i][j] = b * v[i][j];
			}
		}
		return (r);
	}
	Matrix operator+(const int b) {
		Matrix r(row, column);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				r.v[i][j] = b + v[i][j];
			}
		}
		return (r);
	}
	Matrix operator-(const int b) {
		Matrix r(row, column);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				r.v[i][j] = v[i][j] - b;
			}
		}
		return (r);
	}
	void unit_matrix() {
		int n = row;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				v[i][j] = (i == j);
			}
		}
	}
	Matrix<T> accumu_sum() {
		Matrix<T> r(row+1, column+1);
		for (int i = 1; i <= row; i++) {
			for (int j = 1; j <= column; j++) {
				r[i][j] = v[i-1][j-1] + r[i-1][j] + r[i][j-1] - r[i-1][j-1];
			}
		}
		return (r);
	}
	//半開区間で指定
	T get_sum_accumu(int r1, int c1, int r2, int c2) {
		return v[r2][c2] + v[r1][c1] - v[r2][c1] - v[r1][c2];
	}
	Matrix transposed() {
		Matrix t(column, row);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				t[j][i] = v[i][j];
			}
		}
		return (t);
	}
	friend ostream &operator<<(ostream &lhs, const Matrix<T> &rhs) {
		for (int i = 0; i < rhs.row; i++) {
			for (int j = 0; j < rhs.column - 1; j++) {
				lhs << rhs.v[i][j] << " ";
			}
			lhs << rhs.v[i][rhs.column - 1];
			if (i != rhs.row-1) cout << endl;
		}
		return lhs;
	}
	friend istream &operator>>(istream &lhs, Matrix<T> &rhs) {
		for (int i = 0; i < rhs.row; i++) {
			for (int j = 0; j < rhs.column; j++) {
				lhs >> rhs.v[i][j];
			}
		}
		return lhs;
	}
};
```
{% endraw %}

<a href="../../index.html">Back to top page</a>
