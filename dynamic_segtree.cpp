template<class S, S(*op)(S, S), S(*e)()>
class dynamic_segtree {
public:
	dynamic_segtree(size_t n) : n(n), root(nullptr) {}

	void set(size_t p, S x) { set(root, 0, n, p, x); }
	S get(size_t p) { return get(root, 0, n, p); }
	S prod(size_t l, size_t r) { return prod(root, 0, n, l, r); }

private:
	struct node {
		S value;
		node* left, * right;
		node(S value) : value(value), left(nullptr), right(nullptr) {}
	};

	size_t n;
	node* root;

	void set(node*& t, size_t a, size_t b, size_t p, S x) {
		if (not t)t = new node(e());
		if (b - a == 1) {
			t->value = x;
			return;
		}

		size_t c = a + b >> 1;
		if (p < c)set(t->left, a, c, p, x);
		else set(t->right, c, b, p, x);

		t->value = e();
		if (t->left)t->value = t->left->value;
		if (t->right)t->value = op(t->value, t->right->value);
	}

	S get(node*& t, size_t a, size_t b, size_t p) {
		if (not t)return e();
		if (b - a == 1)return t->value;
		size_t c = a + b >> 1;
		if (p < c)return get(t->left, a, c, p);
		else return get(t->right, c, b, p);
	}

	S prod(node*& t, size_t a, size_t b, size_t l, size_t r) {
		if (not t or b <= l or r <= a)return e();
		if (l <= a and b <= r)return t->value;
		size_t c = a + b >> 1;
		return op(prod(t->left, a, c, l, r), prod(t->right, c, b, l, r));
	}
};
