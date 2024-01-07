#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int mod_sqrt(int x, int p) {
	if(!x || p <= 2)
		return x;
	auto mod_pow = [&p](int x, int k) { // 0 <= x < p, k >= 0
		int ret = 1;
		for( ; k > 0; k >>= 1, x = (LL)x * x % p)
			if(k & 1)
				ret = (LL)ret * x % p;
		return ret;
	};
	if(mod_pow(x, (p - 1) / 2) != 1)
		return -1;
	static mt19937 rnd(19260817);
	int w, y;
	do {
		w = rnd() % (p - 1) + 1;
		y = ((LL)w * w + p - x) % p;
	} while(mod_pow(y, (p - 1) / 2) == 1);
	auto mod_mul = [&p, &y](pair<int, int> const &u, pair<int, int> const &v) {
		int fir = ((LL)u.first * v.first + (LL)u.second * v.second % p * y) % p;
		int sec = ((LL)u.first * v.second + (LL)u.second * v.first) % p;
		return make_pair(fir, sec);
	};
	pair<int, int> ret = make_pair(1, 0), tmp = make_pair(w, 1);
	for(int k = (p + 1) / 2; k > 0; k >>= 1, tmp = mod_mul(tmp, tmp))
		if(k & 1)
			ret = mod_mul(ret, tmp);
	return ret.first;
}
const int maxn = (int)3.2e4 + 1, maxc = 9, maxs = 1 << 16 | 1;
int ptot, pr[maxn], d[maxn];
vector<pair<int, int> > solve(int n) {
	int cnt = 0, sz[2] = {}, cur = 0, pre = 1;
	static pair<int, int> pp[maxc], vec[2][maxs];
	int tmp = n;
	for(int i = 0; pr[i] * pr[i] <= tmp; ++i)
		if(tmp % pr[i] == 0) {
			int ex = 0;
			for(tmp /= pr[i], ++ex; tmp % pr[i] == 0; tmp /= pr[i], ++ex);
			pp[cnt++] = make_pair(pr[i], ex << 1);
		}
	if(tmp > 1)
		pp[cnt++] = make_pair(tmp, 2);
	sz[cur] = 1;
	vec[cur][0] = make_pair(0, 1);
	for(int i = 0; i < cnt; ++i) {
		pair<int, int> tr;
		if(pp[i].first == 2) {
			tr = make_pair(1, 1);
		} else if((pp[i].first & 3) == 3) {
			tr = make_pair(0, pp[i].first);
		} else {
			int a = pp[i].first, b = mod_sqrt(pp[i].first - 1, pp[i].first);
			for( ; (LL)b * b > pp[i].first; swap(a, b), b %= a);
			int tmp = pp[i].first - b * b;
			a = (int)sqrt(tmp);
			for( ; a * a < tmp; ++a);
			for( ; a * a > tmp; --a);
			if(a > b)
				swap(a, b);
			tr = make_pair(a, b);
		}
		for(int rem = pp[i].second; rem > 0; rem -= (pp[i].first & 3) == 3 ? 2 : 1) {
			swap(pre, cur);
			sz[cur] = 0;
			for(int j = 0; j < sz[pre]; ++j) {
				int a = vec[pre][j].first, b = vec[pre][j].second;
				{
					int c = a * tr.first + b * tr.second;
					int d = abs(a * tr.second - b * tr.first);
					if(c > d)
						swap(c, d);
					vec[cur][sz[cur]++] = make_pair(c, d);
				}
				{
					int c = abs(a * tr.first - b * tr.second);
					int d = a * tr.second + b * tr.first;
					if(c > d)
						swap(c, d);
					vec[cur][sz[cur]++] = make_pair(c, d);
				}
			}
			assert(sz[cur] <= maxs);
			sort(vec[cur], vec[cur] + sz[cur]);
			sz[cur] = unique(vec[cur], vec[cur] + sz[cur]) - vec[cur];
		}
	}
	vector<pair<int, int> > ret;
	ret.reserve(sz[cur] << 3);
	for(int i = 0; i < sz[cur]; ++i) {
		int a = vec[cur][i].first, b = vec[cur][i].second;
		ret.push_back(make_pair(a, b));
		ret.push_back(make_pair(-a, b));
		ret.push_back(make_pair(a, -b));
		ret.push_back(make_pair(-a, -b));
		ret.push_back(make_pair(b, a));
		ret.push_back(make_pair(-b, a));
		ret.push_back(make_pair(b, -a));
		ret.push_back(make_pair(-b, -a));
	}
	sort(ret.begin(), ret.end());
	ret.erase(unique(ret.begin(), ret.end()), ret.end());
	return ret;
}
int main() {
	for(int i = 2; i < maxn; ++i) {
		if(!d[i])
			pr[ptot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	pr[ptot] = maxn;
	int t, a, b, c;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d", &a, &b, &c);
		vector<pair<int, int> > lft = solve(a), rht = solve(b);
		vector<pair<pair<int, int>, pair<int, int> > > ans;
		for(auto &it : lft)
			for(auto &jt : rht) {
				int dx = it.first - jt.first;
				int dy = it.second - jt.second;
				if((LL)dx * dx + (LL)dy * dy == (LL)c * c)
					ans.push_back(make_pair(it, jt));
			}
		printf("%d\n", (int)ans.size());
		for(auto &it : ans) {
			auto &lft = it.first, &rht = it.second;
			printf("%d %d %d %d\n", lft.first, lft.second, rht.first, rht.second);
		}
	}
	return 0;
}