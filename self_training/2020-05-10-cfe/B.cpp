#include <bits/stdc++.h>
using namespace std;
typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LDB;
const int maxn = (int)3e5 + 1, maxd = 26, mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const DB pi = acos((DB)-1);

int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		static char buf[maxn];
		scanf("%s", buf);
		int len = strlen(buf), cnt[2] = {};
		for(int i = 0; i < len; ++i)
			++cnt[(int)(buf[i] - '0')];
		if(min(cnt[0], cnt[1]) > 0) {
			len <<= 1;
			for(int i = 0; i < len; ++i)
				buf[i] = "01"[i & 1];
			buf[len] = '\0';
		}
		puts(buf);
	}
	return 0;
}