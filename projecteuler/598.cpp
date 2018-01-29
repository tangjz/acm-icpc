#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 101;
int tot, pr[maxn], d[maxn];
int main() {
	for(int i = 2; i < maxn; ++i) {
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	pr[tot] = maxn;
	int n;
	while(scanf("%d", &n) == 1) {
		map<pair<LL, LL>, LL> pre, cur, mid;
		cur[make_pair(1LL, 1LL)] = 1;
		for(int i = 0, las = -1; (LL)pr[i] * pr[i] <= n; ++i) {
			int val = 0;
			for(int tmp = n / pr[i]; tmp; val += tmp, tmp /= pr[i]);
			if(las != val) {
				printf("\n%d:", val);
				las = val;
			}
			printf(" %d", pr[i]);
			cur.swap(pre);
			map<pair<LL, LL>, LL>().swap(cur);
			for(map<pair<LL, LL>, LL>::iterator it = pre.begin(); it != pre.end(); ++it) {
				LL fz = it -> first.first, fm = it -> first.second, ways = it -> second;
				for(int j = 0; j <= val; ++j) {
					LL nfz = fz * (j + 1), nfm = fm * (val - j + 1), r = __gcd(nfz, nfm);
					cur[make_pair(nfz / r, nfm / r)] += ways;
				}
			}
			printf("(%lld)", (LL)cur.size());
		}
		cur.swap(mid);
		map<pair<LL, LL>, LL>().swap(cur);
		cur[make_pair(1LL, 1LL)] = 1;
		for(int i = tot, las = -1; (LL)pr[i] * pr[i] > n; --i) {
			if(n < pr[i])
				continue;
			int val = 0;
			for(int tmp = n / pr[i]; tmp; val += tmp, tmp /= pr[i]);
			if(las != val) {
				printf("\n%d:", val);
				las = val;
			}
			printf(" %d", pr[i]);
			cur.swap(pre);
			map<pair<LL, LL>, LL>().swap(cur);
			for(map<pair<LL, LL>, LL>::iterator it = pre.begin(); it != pre.end(); ++it) {
				LL fz = it -> first.first, fm = it -> first.second, ways = it -> second;
				for(int j = 0; j <= val; ++j) {
					LL nfz = fz * (j + 1), nfm = fm * (val - j + 1), r = __gcd(nfz, nfm);
					cur[make_pair(nfz / r, nfm / r)] += ways;
				}
			}
			printf("(%lld)", (LL)cur.size());
		}
		LL ans = 0;
		if(mid.size() < cur.size())
			mid.swap(cur);
		for(map<pair<LL, LL>, LL>::iterator it = cur.begin(); it != cur.end(); ++it) {
			LL fz = it -> first.first, fm = it -> first.second, ways = it -> second;
			if(mid.count(make_pair(fm, fz)))
				ans += mid[make_pair(fm, fz)] * ways;
		}
		printf("\nanswer: %lld\n", ans >> 1);
	}
	return 0;
}
