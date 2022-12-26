#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
#define x first
#define y second
const int maxn = (int)2e5 + 1, maxc = 26, mod = (int)1e9 + 7;
int n, m, pos[maxn];
char buf[maxn], pat[maxn];
int main() {
	int t = 1;
	// scanf("%d", &t);
	while(t--) {
		scanf("%s%s", buf, pat);
		n = strlen(buf);
		m = strlen(pat);
		for(int i = 0; i < n; ++i) {
			int x;
			scanf("%d", &x);
			pos[--x] = i;
		}
		int L = 0, R = n - 1;
		while(L < R) {
			int M = (L + R + 1) >> 1;
			int ctr = 0;
			for(int i = 0; ctr < m && i < n; ++i)
				if(pos[i] >= M)
					ctr += buf[i] == pat[ctr];
			if(ctr == m) {
				L = M;
			} else {
				R = M - 1;
			}
		}
		printf("%d\n", L);
	}
	return 0;
}