#include <bits/stdc++.h>
using namespace std;
template<class T> bool chmin(T& a, T b) { return a > b ? a = b, true : false; }
template<class T> bool chmax(T& a, T b) { return a < b ? a = b, true : false; }
template<typename T1, typename T2> istream& operator>>(istream& is, pair<T1, T2>& p) { is >> p.first >> p.second; return is; }
template<class R> requires ranges::input_range<R> && (!convertible_to<R, string_view>)
ostream& operator<<(ostream& os, R&& range) { for (auto& element : range) os << element << ' '; return os; }
template<typename T> requires ranges::input_range<T> && (!is_same_v<T, string>)
istream& operator>>(std::istream& is, T& container) { for (auto& e : container)is >> e; return is; }
struct column_fn {
	size_t k;
	template<ranges::viewable_range R>
	auto operator()(R&& r)const { return forward<R>(r) | std::views::transform([k = k](auto&& row) -> decltype(auto) { return row[k]; }); }
	template<ranges::viewable_range R>
	friend auto operator|(R&& r, column_fn f) { return f(forward<R>(r)); }
};
inline auto column(size_t k) { return column_fn{ k }; }
using ll = long long;
using ull = unsigned long long;
using uint = unsigned int;
template<class T = ll> struct Edge {
	ll to;
	T weight;
	bool operator==(Edge e) { return this->to == e.to and this->weight == e.weight; }
	bool operator<(Edge e) { return this->to == e.to ? this->weight < e.weight : this->to < e.to; }
};
template<class T = ll>
using Graph = vector<vector<T>>;

#ifdef _DEBUG
#define SHOW(n) {const auto _ret = n; cerr << #n << ": " << _ret << endl;}
#define LOG(x) cerr << x << endl;
#else
#define SHOW(n)
#define LOG(x)
#endif

//AtCoder Library
#include <atcoder/all>
using namespace atcoder;
using mint = modint998244353;
//using mint = modint1000000007;
using mint1 = dynamic_modint<0>;
//using mint = modint;
//mint::set_mod();
istream& operator>>(istream& is, mint& x) { ll r; is >> r; x = r; return is; }
ostream& operator<<(ostream& os, mint& x) { os << x.val(); return os; }

//boost
//#include <boost/multiprecision/cpp_int.hpp>
//using namespace boost::multiprecision;
//using l3 = int128_t;



int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);




	return 0;
};
