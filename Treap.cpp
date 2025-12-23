template<class S, S(*op)(S, S), S(*e)()>
class Treap {
	mt19937 mt;
	uniform_int_distribution<int> rnd;

	struct Node {
		S val;
		Node* lch, * rch;
		int pri;
		int siz;
		S sum;
		bool rev;
		Node(S v, int p) :val(v), pri(p), siz(1), sum(v), rev(false) {
			lch = nullptr;
			rch = nullptr;
		}
	};
	Node* root = nullptr;

	int size(Node* t) {
		if (t == nullptr)return 0;
		return t->siz;
	}
	S prod(Node* t) {
		if (t == nullptr)return e();
		return t->sum;
	}

	void push(Node* t) {
		if (t == nullptr)return;
		if (t->rev) {
			swap(t->lch, t->rch);
			if (t->lch)t->lch->rev ^= true;
			if (t->rch)t->rch->rev ^= true;
			t->rev = false;
		}
	}

	Node* update(Node* t) {
		t->siz = size(t->lch) + size(t->rch) + 1;
		t->sum = op(op(prod(t->lch), t->val), prod(t->rch));
		return t;
	}

	Node* merge(Node* l, Node* r) {
		push(l);
		push(r);
		if (l == nullptr)return r;
		if (r == nullptr)return l;

		if (l->pri > r->pri) {
			l->rch = merge(l->rch, r);
			return update(l);
		}
		else {
			r->lch = merge(l, r->lch);
			return update(r);
		}
	}

	pair<Node*, Node*> split(Node* t, int k) {
		if (t == nullptr)return { nullptr,nullptr };

		push(t);
		if (k <= size(t->lch)) {
			pair<Node*, Node*> s = split(t->lch, k);
			t->lch = s.second;
			return { s.first,update(t) };
		}
		else {
			pair<Node*, Node*> s = split(t->rch, k - size(t->lch) - 1);
			t->rch = s.first;
			return { update(t),s.second };
		}
	}

	Node* insert(Node* t, int k, S v) {
		auto [l, r] = split(t, k);
		Node* ret = merge(l, new Node(v, rnd(mt)));
		ret = merge(ret, r);
		return ret;
	}

	Node* erase(Node* t, int k) {
		auto [l, r_aux] = split(t, k);
		auto [m, r] = split(r_aux, 1);
		delete m;
		return merge(l, r);
	}

	void reverse(Node* t, int l, int r) {
		auto [b_aux, c] = split(t, r);
		auto [a, b] = split(b_aux, l);
		if (b != nullptr)b->rev ^= true;
		auto t_aux = merge(a, b);
		t = merge(t_aux, c);
	}

	void rotate(Node* t, int l, int m, int r) {
		reverse(t, l, r);
		reverse(t, l, l + r - m);
		reverse(t, l + r - m, r);
	}

public:
	Treap() :mt(0), rnd(0) {}

	int size() {
		return size(root);
	}

	void insert(int k, S v) {
		assert(0 <= k and k <= size(root));
		root = insert(root, k, v);
	}

	void erase(int k) {
		assert(0 <= k and k < size(root));
		root = erase(root, k);
	}

	S prod(int l, int r) {
		assert(0 <= l and l <= r and r <= size(root));
		auto [a, b] = split(root, r);
		auto [c, d] = split(a, l);

		S ret = prod(d);

		root = merge(merge(c, d), b);

		return ret;
	}

	S operator[](int k) {
		assert(0 <= k and k < size(root));
		return prod(k, k + 1);
	}

	void reverse(int l, int r) {
		assert(0 <= l and l <= r and r <= size(root));
		reverse(root, l, r);
	}

	void rotate(int l, int m, int r) {
		assert(0 <= l and l <= m and m <= r and r <= size(root));
		rotate(root, l, m, r);
	}

	void debug() {
		int n = size(root);
		if (n > 0)push(root);
		for (int i = 0; i < n; ++i) {
			cerr << (*this)[i] << " ";
		}
		cerr << endl;
	}
};
