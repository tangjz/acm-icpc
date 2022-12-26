#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
#define x first
#define y second
const int maxn = (int)1e5 + 1, maxc = 26, mod = (int)1e9 + 7;
int main() {
	int t = 1;
	// scanf("%d", &t);
	while(t--) {
		static char s[maxn], t[maxn];
		scanf("%s%s", &s, &t);
		int slen = strlen(s);
		int tlen = strlen(t);
		static int cnt[maxc + 1];
		memset(cnt, 0, maxc * sizeof(int));
		for(int i = 0; i < tlen - 1; ++i)
			++cnt[(int)(t[i] - 'a')];
		LL ans = (LL)slen * tlen;
		for(int i = 1; i < slen; ++i)
			ans -= cnt[(int)(s[i] - 'a')];
		printf("%lld\n", ans);
	}
	return 0;
}