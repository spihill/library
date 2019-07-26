#include <bits/stdc++.h>

using namespace std;

namespace spihill {
template<class T>
class AVLSetIterator;

template<class T, class Compare = less<T>>
struct AVLSet {
	struct NODE;
	struct NODE_LIST;
	NODE_LIST list_dummy;
	NODE node_dummy;
	friend AVLSetIterator<T>;
	using iterator = AVLSetIterator<T>;
	AVLSet() {
		node_dummy.index = &list_dummy;
		list_dummy.node = &node_dummy;
	}
	AVLSet(const AVLSet& R) {
		node_dummy.index = &list_dummy;
		list_dummy.node = &node_dummy;
		auto dfs = [&](auto f, NODE* old_node, NODE* new_node) {
			if (0) return new_node;
			if (old_node->left) {
				new_node->left = f(f, old_node->left, new NODE((T&&) *(old_node->left->key), new_node));
			}
			auto l = new NODE_LIST(&list_dummy, true);
			l->node = new_node;
			new_node->index = l;
			new_node->child_size = old_node->child_size;
			new_node->height = old_node->height;
			if (old_node->right) {
				new_node->right = f(f, old_node->right, new NODE((T&&) *(old_node->right->key), new_node));
			}
			return new_node;
		};
		if (R.node_dummy.left) node_dummy.left = dfs(dfs, R.node_dummy.left, new NODE((T&&) *(R.node_dummy.left->key), &node_dummy));
	}
	AVLSet& operator=(const AVLSet& R) {
		for (NODE_LIST* p = list_dummy.fp; p != &list_dummy;) {
			p = p->fp;
			delete p->bp;
		}
		node_dummy.index = &list_dummy;
		list_dummy.node = &node_dummy;
		auto dfs = [&](auto f, NODE* old_node, NODE* new_node) {
			if (0) return new_node;
			if (old_node->left) {
				new_node->left = f(f, old_node->left, new NODE((T&&) *(old_node->left->key), new_node));
			}
			auto l = new NODE_LIST(&list_dummy, true);
			l->node = new_node;
			new_node->index = l;
			new_node->child_size = old_node->child_size;
			new_node->height = old_node->height;
			if (old_node->right) {
				new_node->right = f(f, old_node->right, new NODE((T&&) *(old_node->right->key), new_node));
			}
			return new_node;
		};
		if (R.node_dummy.left) node_dummy.left = dfs(dfs, R.node_dummy.left, new NODE((T&&) *(R.node_dummy.left->key), &node_dummy));
		return *this;
	}
	~AVLSet() {
		for (NODE_LIST* p = list_dummy.fp; p != &list_dummy;) {
			p = p->fp;
			delete p->bp;
		}
	}
	int size() {
		if (node_dummy.left) return node_dummy.left->child_size;
		return 0;
	}
	struct NODE_LIST {
		NODE_LIST* fp;
		NODE_LIST* bp;
		NODE* node;
		bool dummy = false;
		NODE_LIST() : fp(this), bp(this), node(nullptr), dummy(true) {}
		NODE_LIST(NODE_LIST* p, bool is_left) : node(nullptr) {
			NODE_LIST* pre = is_left ? p->bp : p;
			NODE_LIST* nex = is_left ? p : p->fp;
			bp = pre;
			fp = nex;
			pre->fp = this;
			nex->bp = this;
		}
		~NODE_LIST() {
			if (!dummy) delete node;
		}
		int get_position() {
			int result = -1;
			bool is_left = false;
			NODE* n = node;
			for (;; n = n->par) {
				if (!is_left) result += n->left ? n->left->child_size + 1 : 1;
				if (n->par) is_left = (n->par->left == n);
				else break;
			}
			return result;
		}
	};
	void remove_list(NODE_LIST* p) {
		p->bp->fp = p->fp;
		p->fp->bp = p->bp;
		delete p;
	}
	void remove_node(NODE* n, bool is_left) {
		if (n->par->left == n) n->par->left = is_left ? n->left : n->right;
		else  n->par->right = is_left ? n->left : n->right;
		if (is_left) n->left->par = n->par;
		else n->right->par = n->par;
		for (NODE* i = n->par; i != &node_dummy; i = i->par) i->child_size--;
		remove_list(n->index);
	}
	void remove_node(NODE* n) {
		if (n->par->left == n) n->par->left = nullptr;
		else  n->par->right = nullptr;
		for (NODE* i = n->par; i != &node_dummy; i = i->par) i->child_size--;
		remove_list(n->index);
	}
	struct NODE {
		T* key;
		NODE_LIST* index;
		NODE* left;
		NODE* right;
		NODE* par;
		int child_size;
		int height;
		NODE() : key(nullptr), index(nullptr), left(nullptr), right(nullptr), par(nullptr), child_size(0), height(0) {}
		NODE(T&& d, NODE* par_) : index(nullptr), left(nullptr) , right(nullptr), par(par_), child_size(1), height(1) {key = new T(d);}
		~NODE() {delete key;}
		void RotateR() {
			NODE* P = this;
			NODE* R = this->par;
			NODE* l = this->left;
			NODE* B = l->right;
			if (R->left == P) R->left = l;
			else R->right = l;
			l->par = R;
			if (B) B->par = P;
			P->left = B;
			l->right = P;
			P->par = l;
			int B_size = B ? B->child_size : 0;
			P->child_size += B_size - l->child_size;
			l->child_size += P->child_size - B_size;
			P->update_height();
			l->update_height();
		}
		void RotateL() {
			NODE* P = this;
			NODE* R = this->par;
			NODE* r = this->right;
			NODE* B = r->left;
			if (R->left == P) R->left = r;
			else R->right = r;
			r->par = R;
			if (B) B->par = P;
			P->right = B;
			r->left = P;
			P->par = r;
			int B_size = B ? B->child_size : 0;
			P->child_size += B_size - r->child_size;
			r->child_size += P->child_size - B_size;
			P->update_height();
			r->update_height();
		}
		void RotateRL() {
			right->RotateR();
			RotateL();
		}
		void RotateLR() {
			left->RotateL();
			RotateR();
		}
		int bias() {
			int L = left  ? left->height  : 0;
			int R = right ? right->height : 0;
			return L - R;
		}
		void update_height() {
			int L = left  ? left->height  : 0;
			int R = right ? right->height : 0;
			height = max(L, R) + 1;
		}
	};
	void balancing_insert(NODE* parent) {
		for (;!(parent->index->dummy); parent = parent->par) {
			parent->update_height();
			if (parent->bias() == 0) return;
			if (abs(parent->bias()) != 1) break;
		}
		if (parent != &node_dummy) balancing_rotate(parent);
	}
	void balancing_erase(NODE* parent) {
		for (;; parent = parent->par->par) {
			for (;!(parent->index->dummy); parent = parent->par) {
				parent->update_height();
				if (abs(parent->bias()) == 1) return;
				if (parent->bias() != 0) break;
			}
			if (parent == &node_dummy) return;
			balancing_rotate(parent);
		}
	}
	void balancing_rotate(NODE* parent) {
		if (parent->bias() == 2) {
			if (parent->left->bias() == -1) parent->RotateLR();
			else parent->RotateR();
		} else {
			if (parent->right->bias() == 1) parent->RotateRL();
			else parent->RotateL();
		}
	}
	iterator erase(T&& k) {
		NODE* now = node_dummy.left;
		while (now) {
			if (Compare()(k, *(now->key))) now = now->left;
			else if (Compare()(*(now->key), k)) now = now->right;
			else break;
		}
		if (now == nullptr) return iterator(&list_dummy);
		NODE* target;
		if (now->left) target = now->index->bp->node;
		else target = now;
		assert(target->child_size <= 2);
		NODE_LIST* res = now->index->fp;
		swap(now->key, target->key);
		now = target->par;
		bool is_left = (now->left == target);
		if (target->left) remove_node(target, true);
		else if (target->right) remove_node(target, false);
		else remove_node(target);
		balancing_erase(now);
		return iterator(res);
	}
	iterator erase(const T& k) {
		return erase((T&&) k);
	}
	iterator insert(T&& k) {
		NODE* parent = &node_dummy;
		NODE* now = parent->left;
		bool is_left = true;
		while (now) {
			parent = now;
			now->child_size++;
			if (is_left = Compare()(k, *(now->key))) now = now->left;
			else now = now->right;
		}
		NODE* child = new NODE((T&&) k, parent);
		if (is_left) parent->left = child;
		else parent->right = child;
		child->index = new NODE_LIST(parent->index, is_left);
		child->index->node = child;
		balancing_insert(parent);
		return iterator(child->index);
	}
	iterator insert(const T& k) {
		return insert((T&&) k);
	}
	int count(T&& v) {
		enum STATUS {LEFT, RIGHT, NEUTRAL};
		int sum = 0;
		queue<pair<STATUS, NODE*>> q;
		q.emplace(NEUTRAL, node_dummy.left);
		while (!q.empty()) {
			pair<STATUS, NODE*> t = q.front();
			q.pop();
			int status = t.first;
			NODE* n = t.second;
			if (n == nullptr) continue;
			if (status == NEUTRAL) {
				if (Compare()(v, *(n->key))) q.emplace(NEUTRAL, n->left);
				else if (Compare()(*(n->key), v)) q.emplace(NEUTRAL, n->right);
				else {
					sum++;
					q.emplace(LEFT, n->left);
					q.emplace(RIGHT, n->right);
				}
			} else if (status == LEFT) {
				if (Compare()(*(n->key), v)) q.emplace(LEFT, n->right);
				else {
					sum += (n->right ? n->right->child_size : 0) + 1;
					q.emplace(LEFT, n->left);
				}
			} else /* if (status == RIGHT) */{
				if (Compare()(v, *(n->key))) q.emplace(RIGHT, n->left);
				else {
					sum += (n->left ? n->left->child_size : 0) + 1;
					q.emplace(RIGHT, n->right);
				}
			}
		}
		return sum;
	}
	int count(const T& v) {
		return count((T&&) v);
	}
	bool is_balanced() {
		auto dfs = [&](auto f, NODE* n, int& height, int& c_size) {
			if (0) return false;
			if (n == nullptr) {
				height = 0;
				c_size = 0;
				return true;
			}
			int L = 0, R = 0;
			c_size = 1;
			int t;
			if (!f(f, n->left, L, t)) return false;
			c_size += t;
			if (!f(f, n->right, R, t)) return false;
			c_size += t;
			height = max(L, R) + 1;
			if (n->height != height) {
				cerr << "hight value is odd." << endl;
				return false;
			}
			if (n->bias() < -2 || n->bias() > 2) {
				cerr << "bias value is odd." << endl;
				cerr << "bias : " << n->bias() << endl;
				return false;
			}
			if (c_size != n->child_size) {
				cerr << "child_size is wrong" << endl;
				cerr << "size : " << n->child_size << endl;
				cerr << "real : " << c_size << endl;
				return false;
			}
			height = std::max(L, R) + 1;
			return true;
		};
		int t, u;
		return dfs(dfs, node_dummy.left, t, u);
	}
	iterator begin() {
		return iterator(list_dummy.fp);
	}
	iterator end() {
		return iterator(&list_dummy);
	}
	iterator lower_bound(T&& v) {
		NODE* now = node_dummy.left;
		NODE* ans = nullptr;
		while (now != nullptr) {
			if (Compare()(*(now->key), v)) {
				now = now->right;
			}
			else {
				ans = now;
				now = now->left;
			}
		}
		if (ans) return iterator(ans->index);
		return iterator(&list_dummy);
	}
	iterator lower_bound(const T& v) {
		return lower_bound((T&&) v);
	}
	iterator upper_bound(T&& v) {
		NODE* now = node_dummy.left;
		NODE* ans = nullptr;
		while (now != nullptr) {
			if (Compare()(v, *(now->key))) {
				ans = now;
				now = now->left;
			}
			else {
				now = now->right;
			}
		}
		if (ans) return iterator(ans->index);
		return iterator(&list_dummy);
	}
	iterator upper_bound(const T& v) {
		return upper_bound((T&&) v);
	}
	const T& get_kth_element(int k) {
		if (k < 0 || size() <= k) throw out_of_range("Error at AVLSet::get_kth_element(int)");
		int pos = 0;
		NODE* now = node_dummy.left;
		while (true) {
			int L = now->left ? now->left->child_size : 0;
			if (Compare()(pos + L, k)) pos += L + 1, now = now->right;
			else if (Compare()(k, L + pos)) now = now->left;
			else break;
		}
		return *(now->key);
	}
};
template<class T>
class AVLSetIterator {
	friend AVLSet<T>;
	using NODE_LIST = typename AVLSet<T>::NODE_LIST;
	NODE_LIST* list_ptr;
	AVLSetIterator(NODE_LIST* n) : list_ptr(n) {}
public:
	AVLSetIterator(const AVLSetIterator& R) : list_ptr(R.list_ptr) {}
	AVLSetIterator& operator++() {
		if (list_ptr->dummy) throw out_of_range("Error at AVLSetIterator& operator++()");
		list_ptr = list_ptr->fp;
		return *this;
	}
	AVLSetIterator operator++(int unused) {
		if (list_ptr->dummy) throw out_of_range("Error at AVLSetIterator operator++(int)");
		AVLSetIterator result = *this;
		list_ptr = list_ptr->fp;
		return result;
	}
	AVLSetIterator& operator--() {
		if (list_ptr->bp->dummy) throw out_of_range("Error at AVLSetIterator& operator--()");
		list_ptr = list_ptr->bp;
		return *this;
	}
	AVLSetIterator operator--(int unused) {
		if (list_ptr->bp->dummy) throw out_of_range("Error at AVLSetIterator operator--(int)");
		AVLSetIterator result = *this;
		list_ptr = list_ptr->bp;
		return result;
	}
	int operator-(const AVLSetIterator& R) {
		return list_ptr->get_position() - R.list_ptr->get_position();
	}
	const T& operator*() const {
		assert(list_ptr->node->key);
		return *(list_ptr->node->key);
	}
	bool operator==(const AVLSetIterator& R) {
		return this->list_ptr == R.list_ptr;
	}
	bool operator!=(const AVLSetIterator& R) {
		return !(*this == R);
	}
};
} // namespace

using namespace spihill;

void check_insert(const int);
void check_erase(const int);
bool check(AVLSet<int>& R, multiset<int>& S);

int main()
{
	cout << "INSERT TEST" << endl;
	check_insert(100000);
	cout << "TEST PASSED" << endl;
	cout << "ERASE TEST" << endl;
	check_erase(100000);
	cout << "TEST PASSED" << endl;
}

void check_insert(const int MAX)
{
	AVLSet<int> R_random_big;
	AVLSet<int> R_random_small;
	AVLSet<int> R_increase;
	AVLSet<int> R_decrease;

	multiset<int> S_random_big;
	multiset<int> S_random_small;
	multiset<int> S_increase;
	multiset<int> S_decrease;

	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());

	std::uniform_real_distribution<> dist1(-1.0, 1.0);

	for (int i = -MAX; i < MAX; i++) {
		int big = 1000000000 * dist1(engine);
		int small = 100 * dist1(engine);
		R_random_big.insert(big);
		R_random_small.insert(small);
		R_increase.insert(i);
		R_decrease.insert(-i);
		S_random_big.insert(big);
		S_random_small.insert(small);
		S_increase.insert(i);
		S_decrease.insert(-i);
	}

	auto R_copy(R_random_big);
	auto S_copy = S_random_big;
	AVLSet<int> R_assign;
	R_assign = R_random_big;
	for (int i = -MAX; i < MAX; i++) {
		int big = 1000000000 * dist1(engine);
		R_copy.insert(big);
		R_assign.insert(big);
		S_copy.insert(big);
	}
	assert(check(R_increase, S_increase));
	assert(check(R_decrease, S_decrease));
	assert(check(R_random_big, S_random_big));
	assert(check(R_random_small, S_random_small));
	assert(check(R_copy, S_copy));
	assert(check(R_assign, S_copy));
	assert(R_increase.is_balanced());
	assert(R_decrease.is_balanced());
	assert(R_random_big.is_balanced());
	assert(R_random_small.is_balanced());
	assert(R_copy.is_balanced());
	assert(R_assign.is_balanced());
	return;
}


void check_erase(const int MAX)
{
	AVLSet<int> R_random_small;
	AVLSet<int> R_increase;
	AVLSet<int> R_decrease;
	AVLSet<int> R_nothing;

	multiset<int> S_random_small;
	multiset<int> S_increase;
	multiset<int> S_decrease;
	multiset<int> S_nothing;

	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());

	std::uniform_real_distribution<> dist1(-1.0, 1.0);

	for (int i = -MAX; i < MAX; i++) {
		int big = 1000000000 * dist1(engine);
		int small = 100 * dist1(engine);
		R_random_small.insert(small);
		R_increase.insert(i);
		R_decrease.insert(i);
		R_nothing.insert(big);
		S_random_small.insert(small);
		S_increase.insert(i);
		S_decrease.insert(i);
	}
	for (int i = 0; i < MAX; i++) {
		R_increase.erase(-i - 1);
		R_decrease.erase(i);
		S_increase.erase(-i - 1);
		S_decrease.erase(i);
	}

	for (int i = -100; i <= 100; i++) {
		assert(R_random_small.count(i) == (int) S_random_small.count(i));
		assert((int) S_random_small.count(i) == R_random_small.upper_bound(i) - R_random_small.lower_bound(i));
	}

	for (int i = 0; i < 10; i++) {
		int small = 100 * dist1(engine);
		while (R_random_small.erase(small) != R_random_small.end());
		S_random_small.erase(small);
	}

	for (int i = -100; i <= 100; i++) {
		assert(R_random_small.count(i) == (int) S_random_small.count(i));
		assert((int) S_random_small.count(i) == R_random_small.upper_bound(i) - R_random_small.lower_bound(i));
	}


	while (R_nothing.erase(*(R_nothing.begin())) != R_nothing.end());

	assert(check(R_increase, S_increase));
	assert(check(R_decrease, S_decrease));
	assert(check(R_random_small, S_random_small));
	assert(check(R_nothing, S_nothing));
	assert(R_increase.is_balanced());
	assert(R_random_small.is_balanced());
	assert(R_decrease.is_balanced());
	return;
}

bool check(AVLSet<int>& A, multiset<int>& S)
{
	auto S_itr = S.begin();
	auto A_itr = A.begin();
	for (;A_itr != A.end(); S_itr++, A_itr++) {
		if (*S_itr != *A_itr) return false;
	}
	return S_itr == S.end();
}
