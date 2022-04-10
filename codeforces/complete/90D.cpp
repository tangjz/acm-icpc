#include <bits/stdc++.h>
using namespace std;

typedef signed i32;
typedef unsigned u32;
typedef long long i64;
typedef unsigned long long u64;
// typedef __int128_t i128;
// typedef __uint128_t u128;
typedef float f32;
typedef double f64;
typedef long double f128;

const int maxn = (int)1e6 + 1, maxm = (int)4e6 + 1;
const int maxd = 21, maxc = 26;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const f64 pi = acos((f64)-1), eps = 1e-12;

inline int sgn(f64 x) {
	return (x > eps) - (x < -eps);
}

void solve() {
	typedef struct {
		int t, b, s, deg;
		i64 shape[2];
		vector<int> sub;
	} Node;
	int n = 0, m;
	unordered_map<string, int> idx;
	vector<Node> nodes;
	auto getID = [&](char buf[]) {
		string pat = buf;
		auto it = idx.find(pat);
		if(it != idx.end())
			return it -> second;
		int tot = nodes.size();
		idx.insert({move(pat), tot});
		nodes.push_back((Node){});
		return tot;
	};
	scanf("%d", &m);
	while(m--) {
		static char buf[maxn];
		scanf("%s", buf);
		if(buf[0] >= 'A' && buf[0] <= 'Z') {
			int t = buf[0] == 'W' ? 2 : (buf[0] == 'V');
			scanf("%s", buf);
			if(t != 2) {
				nodes[getID(buf)].t = t;
				continue;
			}
			int pos = 0;
			for( ; buf[pos] != '('; ++pos);
			buf[pos] = '\0';
			Node &cur = nodes[getID(buf)];
			cur.t = t;
			for(int i = 0; i < 2; ++i)
				for(++pos; buf[pos] != ',' && buf[pos] != ')'; ++pos)
					cur.shape[i] = cur.shape[i] * 10 + (buf[pos] - '0');
			continue;
		}
		int pos = 0;
		for( ; buf[pos] != '.'; ++pos);
		buf[pos] = '\0';
		Node &cur = nodes[getID(buf)];
		if(buf[++pos] == 'p') {
			for( ; buf[pos] != '('; ++pos);
			int sta = ++pos;
			for( ; buf[pos] != ')'; ++pos);
			buf[pos] = '\0';
			int id = getID(buf + sta);
			cur.sub.push_back(id);
			++nodes[id].deg;
			continue;
		}
		for( ; buf[pos] != '_'; ++pos);
		int &val = buf[++pos] == 'b' ? cur.b : cur.s;
		val = 0;
		for( ; buf[pos] != '('; ++pos);
		for(++pos; buf[pos] != ')'; ++pos)
			val = val * 10 + (buf[pos] - '0');
	}
	vector<int> que;
	for(int i = 0; i < (int)nodes.size(); ++i)
		if(!nodes[i].deg)
			que.push_back(i);
	for(int i = 0; i < (int)que.size(); ++i) {
		Node &cur = nodes[que[i]];
		for(int id: cur.sub)
			if(!(--nodes[id].deg))
				que.push_back(id);
	}
	for(int i = (int)que.size() - 1; i >= 0; --i) {
		Node &cur = nodes[que[i]];
		if(cur.t == 2)
			continue;
		for(int id: cur.sub) {
			Node &nxt = nodes[id];
			cur.shape[cur.t] += nxt.shape[cur.t];
			cur.shape[!cur.t] = max(cur.shape[!cur.t], nxt.shape[!cur.t]);
		}
		if(!cur.sub.empty()) {
			cur.shape[cur.t] += ((int)cur.sub.size() - 1) * cur.s + 2 * cur.b;
			cur.shape[!cur.t] += 2 * cur.b;
		}
	}
	vector<string> cand;
	for(auto &it: idx)
		cand.push_back(it.first);
	sort(cand.begin(), cand.end());
	for(auto &it: cand) {
		Node &cur = nodes[idx[it]];
		printf("%s %lld %lld\n", it.c_str(), cur.shape[0], cur.shape[1]);
	}
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		// printf("%d\n", solve());
		solve();
	}
	return 0;
}