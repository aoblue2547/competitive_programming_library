using ll = long long;
template<class T = ll> struct Edge {
	ll to;
	T weight;
	bool operator==(Edge e) { return this->to == e.to and this->weight == e.weight; }
	bool operator<(Edge e) { return this->to == e.to ? this->weight < e.weight : this->to < e.to; }
};
template<class T = ll>
using Graph = vector<vector<T>>;
// ここより上は共通
using DistVertex = pair<ll, ll>;
DistVertex get_next(ll v) { return { v, 1 }; }
DistVertex get_next(Edge<ll> v) { return { v.to, v.weight }; }
template<class T>
concept CanGetDistVertex = requires (T x) { { get_next(x) } -> same_as<DistVertex>; };
template<CanGetDistVertex T = ll>
vector<ll> dijkstra(const Graph<T>& g, ll st) {
	constexpr ll INF = 1e18;
	const int n = g.size();
	vector<ll> dist(n, INF);
	dist[st] = 0;
	priority_queue<DistVertex, vector<DistVertex>, greater<DistVertex>> que;
	que.push({ 0, st });

	while (not que.empty()) {
		auto [d, v] = que.top();
		que.pop();
		if (d < dist[v])continue;

		for (auto sw : g[v]) {
			auto [s, w] = get_next(sw);
			if (chmin(dist[s], dist[v] + w)) {
				que.push({ dist[s], s });
			}
		}
	}

	return dist;
}
