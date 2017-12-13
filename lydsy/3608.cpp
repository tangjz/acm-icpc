#include <cstdio>
#include <cstring>
const int maxn = 100001, maxl = 101, maxs = 10000001, BUFLEN = 50;
int n, len[maxn], fa[maxn], lnk[maxn], nxt[maxn], sz[maxn], sg[maxn], res[maxn];
char buf[maxs + maxn + 1], *str[maxn + 2];
bool pool[maxs], *dp[maxn];
int main() {
	scanf("%d%*d", &n);
	str[0] = buf;
	str[1] = buf + 1;
	for(int i = 1, lcp; i <= n; ++i) {
		scanf("%s", str[i]);
		len[i] = strlen(str[i]);
		for(lcp = 0; lcp < len[i] && str[i - 1][lcp] == str[i][lcp]; ++lcp);
		for(fa[i] = i - 1; lcp < len[fa[i]]; fa[i] = fa[fa[i]]);
		str[i + 1] = str[i] + len[i] + 1;
	}
	dp[n] = pool;
	for(int i = n; i >= 1; --i) {
		++sz[i];
		nxt[i] = lnk[fa[i]];
		lnk[fa[i]] = i;
		sz[fa[i]] += sz[i];
		int sum = 0;
		for(int j = lnk[i]; j; j = nxt[j])
			sum ^= sg[j];
		dp[i][sum] = 1;
		for(int j = lnk[i]; j; j = nxt[j])
			for(int k = 0; k < sz[j]; ++k)
				if(dp[j][k])
					dp[i][sum ^ sg[j] ^ k] = 1;
		for( ; dp[i][sg[i]]; ++sg[i]);
		res[fa[i]] ^= sg[i];
		dp[i - 1] = dp[i] + sz[i];
	}
	if(!res[0]) {
		puts("Can't win at all!!");
		return 0;
	}
	for(int i = 0; i <= n; ++i) {
		if(!res[i]) {
			static int outc = 0;
			int rem = len[i];
			char *ptr = str[i], ch;
			while(rem) {
				int tmp = BUFLEN - outc;
				rem < tmp && (tmp = rem);
				ch = ptr[tmp];
				ptr[tmp] = '\0';
				printf("%s", ptr);
				*(ptr += tmp) = ch;
				rem -= tmp;
				if((outc += tmp) == BUFLEN) {
					outc = 0;
					putchar('\n');
				}
			}
		}
		for(int j = lnk[i]; j; j = nxt[j])
			res[j] ^= res[i] ^ sg[j];
	}
	return 0;
}
