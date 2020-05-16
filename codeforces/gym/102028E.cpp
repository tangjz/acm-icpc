#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxm = 100, maxn = 253, BLEN = 13, BASE = (int)1e9;
struct BigInt {
	int len, num[BLEN];
	void read() {
		static char buf[maxm + 1];
		scanf("%s", buf);
		int slen = strlen(buf);
		memset(num, 0, sizeof num);
		for(len = 0; len * 9 < slen; ++len) {
			int R = slen - len * 9, L = max(R - 9, 0);
			buf[R] = '\0';
			sscanf(buf + L, "%d", num + len);
		}
	}
	void write() {
		printf("%d", num[len - 1]);
		for(int i = len - 2; i >= 0; --i)
			printf("%09d", num[i]);
	}
	bool operator < (BigInt const &t) const {
		if(len != t.len)
			return len < t.len;
		for(int i = len - 1; i >= 0; --i)
			if(num[i] != t.num[i])
				return num[i] < t.num[i];
		return 0;
	}
	BigInt operator * (int const &t) const {
		BigInt ret = {len};
		LL tmp = 0;
		for(int i = 0; i < len; ++i) {
			tmp += (LL)num[i] * t;
			ret.num[i] = tmp % BASE;
			tmp /= BASE;
		}
		if(tmp)
			ret.num[ret.len++] = tmp;
		return ret;
	}
	BigInt operator / (int const &t) const {
		BigInt ret = {len};
		LL tmp = 0;
		for(int i = len - 1; i >= 0; --i) {
			tmp = (LL)tmp * BASE + num[i];
			ret.num[i] = tmp / t;
			tmp %= t;
		}
		assert(tmp == 0);
		return ret;
	}
	int operator % (int const &t) const {
		int ret = 0;
		for(int i = len - 1; i >= 0; --i)
			ret = ((LL)ret * BASE + num[i]) % t;
		return ret;
	}
} INF, prd[maxn], ans[maxn][2], n;
int tot, pr[maxn], d[maxn], t;
int main() {
	INF = prd[0] = ans[0][0] = ans[0][1] = (BigInt){1, {1}};
	for(int i = 0; i < maxm; ++i)
		INF = INF * 10;
	for(int i = 2; i < maxn; ++i) {
		if(!d[i]) {
			pr[tot++] = d[i] = i;
			prd[tot] = prd[tot - 1] * i;
			if(INF < prd[tot])
				break;
			int fz = i, cz = __gcd(ans[tot - 1][1] % fz, fz);
			int fm = i + 1, cm = __gcd(ans[tot - 1][0] % fm, fm);
			ans[tot][0] = ans[tot - 1][0] / cm * (fz / cz);
			ans[tot][1] = ans[tot - 1][1] / cz * (fm / cm);
		}
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		n.read();
		//printf("Case #%d: ", Case);
		int idx = upper_bound(prd, prd + tot, n) - prd - 1;
		ans[idx][0].write();
		putchar('/');
		ans[idx][1].write();
		putchar('\n');
	}
	return 0;
}
