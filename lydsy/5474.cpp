#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL, LL> Info;
const int maxn = (int)1e5 + 1, maxm = 101;
int mod_pow(int x, int k, int m) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % m)
		if(k & 1)
			ret = (LL)ret * x % m;
	return ret;
}
inline Info mod_mul(Info u, Info v, LL m) {
	LL t = (3 * v.second - v.first + m) % m;
	LL a = (u.second * v.second - u.first * v.first) % m;
	LL b = (u.second * t - u.first * v.second) % m;
	return (Info){a < 0 ? a + m : a, b < 0 ? b + m : b};
}
Info mod_pow(Info x, LL k, LL m) {
	if(!k)
		return (Info){m - 1, 0};
	int mx;
	for(mx = 0; (2LL << mx) <= k; ++mx);
	while((--mx) >= 0) {
		x = mod_mul(x, x, m);
		if((k >> mx) & 1) {
			LL t = (3 * x.second - x.first + m) % m;
			x = (Info){x.second, t};
		}
	}
	return x;
}
int tot, pr[maxn], d[maxn];
int getPriPer(int n) {
	static int per[maxn] = {0, 0, 3, 4, 0, 10};
	if(n < maxn && per[n])
		return per[n];
	int len = mod_pow(5, (n - 1) >> 1, n) == 1 ? (n - 1) >> 1 : n + 1, rem = len;
	Info A = (Info){0, 1}, I = (Info){n - 1, 0};
	for(int i = 0; pr[i] * pr[i] <= rem; ++i) {
		if(rem % pr[i] > 0)
			continue;
		for(rem /= pr[i]; rem % pr[i] == 0; rem /= pr[i]);
		for( ; len % pr[i] == 0 && mod_pow(A, len / pr[i], n) == I; len /= pr[i]);
	}
	if(rem > 1 && mod_pow(A, len / rem, n) == I)
		len /= rem;
	if(n < maxn)
		per[n] = len;
	return len;
}
LL getPer(LL n) {
	LL len = 1, rem = n;
	for(int i = 0; pr[i] * pr[i] <= rem; ++i) {
		if(rem % pr[i] > 0)
			continue;
		LL tmp = getPriPer(pr[i]), pw = pr[i];
		for(rem /= pr[i]; rem % pr[i] == 0; rem /= pr[i], tmp *= pr[i], pw *= pr[i]);
		if(!(tmp & 1) && !(pr[i] & 1) && mod_pow((Info){0, 1}, tmp >> 1, pw) == (Info){pw - 1, 0})
			tmp >>= 1;
		len *= tmp / __gcd(len, tmp);
	}
	if(rem > 1) {
		LL tmp = getPriPer(rem);
		len *= tmp / __gcd(len, tmp);
	}
	return len;
}
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
	int t, x, y, n, m, mod;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d%d%d", &x, &y, &n, &m, &mod);
		static LL per[maxm], ans[maxm];
		map<LL, LL> Hash;
		per[0] = mod;
		for(int i = 1; i <= m; ++i) {
			map<LL, LL>::iterator it = Hash.find(per[i - 1]);
			if(it == Hash.end()) {
				per[i] = getPer(per[i - 1]);
				Hash.insert((Info){per[i - 1], per[i]});
			} else {
				per[i] = it -> second;
			}
		}
		ans[m] = n % per[m];
		for(int i = m - 1; i >= 0; --i) {
			Info tmp = mod_pow((Info){0, 1}, ans[i + 1], per[i]);
			ans[i] = (y * tmp.second - x * tmp.first) % per[i];
			if(ans[i] < 0)
				ans[i] += per[i];
		}
		printf("%d\n", (int)ans[0]);
	}
	return 0;
}
