#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL;
typedef pair<ULL, ULL> Info;
const int maxn = 21, maxm = 101;
const ULL maxv = (1ULL << 63) - 1;
int findSplit(int n, int m, int d) {
	static ULL dp[maxn][maxm], pre[maxm], suf[maxm];
	for(int i = 0; i <= n; ++i)
		memset(dp[i], 0, (m + 1) * sizeof(ULL));
	pre[0] = dp[0][0] = 1;
	for(int i = 1; i <= d; ++i) {
		ULL &ctr = (pre[i] = pre[i - 1]);
		for(int j = 1; j <= n; ++j)
			for(int k = i; k <= m; ++k)
				pre[i] += (dp[j][k] += dp[j - 1][k - i]);
	}
	for(int i = 0; i <= n; ++i)
		memset(dp[i], 0, (m + 1) * sizeof(ULL));
	suf[d] = dp[0][0] = 1;
	for(int i = d; i >= 1; --i) {
		ULL &ctr = (suf[i - 1] = suf[i]);
		for(int j = 1; j <= n; ++j)
			for(int k = i; k <= m; ++k)
				ctr += (dp[j][k] += dp[j - 1][k - i]);
	}
	int pos = 0;
	for(int i = 1; i <= d; ++i)
		if(pre[i] + suf[i] < pre[pos] + suf[pos])
			pos = i;
	return pos;
}
int n, m, ex0, ex1;
ULL upp;
vector<Info> pre[maxn][maxm], suf[maxn][maxm];
inline ULL power(int x, int k, ULL upp) {
	if(!x)
		return 0ULL;
	ULL ret = 1, lim = upp / x;
	while(k--) {
		if(ret > lim)
			return upp + 1;
		ret *= x;
	}
	return ret;
}
void update(vector<Info> arr[maxn][maxm], int val) {
	ULL v0 = power(val, ex0, upp), v1 = power(val, ex1, maxv);
	for(int i = 1; i <= n; ++i)
		for(int j = val; j <= m; ++j) {
			vector<Info> &lft = arr[i][j], &rht = arr[i - 1][j - val];
			if(rht.empty())
				continue;
			vector<Info> res;
			res.reserve(lft.size() + rht.size());
			vector<Info>::iterator it = lft.begin(), jt = rht.begin();
			Info nxt = make_pair((jt -> first) + v0, (jt -> second) + v1);
			if(nxt.first > upp)
				jt = rht.end();
			while(it != lft.end() || jt != rht.end())
				if(jt == rht.end() || (it != lft.end() && (it -> first) < nxt.first)) {
					res.push_back(*(it++));
				} else {
					if(it != lft.end() && (it -> first) == nxt.first)
						nxt.second = min(nxt.second, (it++) -> second);
					if(nxt.second <= maxv)
						res.push_back(nxt);
					if((++jt) != rht.end()) {
						nxt = make_pair((jt -> first) + v0, (jt -> second) + v1);
						if(nxt.first > upp)
							jt = rht.end();
					}
				}
			lft.swap(res);
		}
}
int main() {
	scanf("%d%d%d%d%llu", &n, &ex0, &ex1, &m, &upp);
	int d = m;
	for( ; d && (power(d, ex0, upp) > upp || power(d, ex1, maxv) > maxv); --d);
	d = findSplit(n, m, d);
	pre[0][0].push_back(make_pair(0ULL, 0ULL));
	suf[0][0].push_back(make_pair(0ULL, 0ULL));
	for(int i = 1; i <= d; ++i)
		update(pre, i);
	for(int i = m; i > d; --i)
		update(suf, i);
	ULL ans = maxv + 1;
	for(int i = 0; i <= n; ++i)
		for(int j = 0; i + j <= n; ++j)
			for(int k = 0; k <= m; ++k) {
				vector<Info> &lft = pre[i][k], &rht = suf[j][m - k];
				if(lft.empty() || rht.empty())
					continue;
				vector<Info>::iterator it = lft.begin(), jt = --rht.end();
				for( ; it != lft.end(); ++it) {
					for( ; jt != rht.begin() && (it -> first) + (jt -> first) > upp; --jt);
					if((it -> first) + (jt -> first) > upp)
						break;
					if((it -> first) + (jt -> first) == upp) {
						fprintf(stderr, "%lld\n", it -> second + jt -> second);
						ans = min(ans, (it -> second) + (jt -> second));
					}
				}
			}
	printf("%llu\n", ans);
	return 0;
}