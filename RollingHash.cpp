struct RollingHash {
	int n;
	vector<ll> h, hr, pow;
	static const ll base = 100, mod = 2147483647;
	RollingHash(string s) :n(s.size()), h(n + 1), hr(n + 1), pow(n + 1, 1) {
		for (int i = 0; i < n; ++i) {
			h[i + 1] = (h[i] * base + s[i]) % mod;
			hr[i + 1] = (hr[i] * base + s[n - i - 1]) % mod;
			pow[i + 1] = (pow[i] * base) % mod;
		}
	}
	ll get(int l, int r) {
		ll res = h[r] - h[l] * pow[r - l] % mod;
		if (res < 0)res += mod;
		return res;
	}
	// 部分列[l, r)を反転
	ll getrev(int l, int r) {
		ll res = hr[n - l] - hr[n - r] * pow[r - l] % mod;
		if (res < 0)res += mod;
		return res;
	}
	ll merge(int l1, int r1, int l2, int r2) {
		return ((get(l1, r1) * pow[r2 - l2]) % mod + get(l2, r2)) % mod;
	}
	int lcp(int i, int j) {
		int ok = 0, ng = min(n - i, n - j) + 1;
		while (ng - ok > 1) {
			int mid = ok + ng >> 1;
			if (get(i, i + mid) == get(j, j + mid)) ok = mid;
			else ng = mid;
		}
		return ok;
	}
};
