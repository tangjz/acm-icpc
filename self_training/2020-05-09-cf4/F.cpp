#include <bits/stdc++.h>
using namespace std;
typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LDB;
const int maxn = 101, maxd = 26, mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const DB pi = acos((DB)-1);
int dp[2][maxn][maxn][maxn];
int F(int las, int c0, int c1, int c2) {
	if(!c0 && !c1 && !c2)
		return 1;
	if(c0 < 0 || c1 < 0 || c2 < 0)
		return 0;
	int &ret = dp[las][c0][c1][c2];
	if(ret == -1) {
		if(!las) {
			ret = F(0, c0 - 1, c1, c2) || F(1, c0, c1 - 1, c2);
		} else {
			ret = F(0, c0, c1 - 1, c2) || F(1, c0, c1, c2 - 1);
		}
	}
	return ret;
}
int main() {
	memset(dp, -1, sizeof dp);
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int c0, c1, c2;
		scanf("%d%d%d", &c0, &c1, &c2);
		int tot = 0;
		static int arr[maxn + 2];
		for(int i = 0; i < 2; ++i)
			if(F(i, c0, c1, c2)) {
				arr[tot++] = i;
				int las = i;
				while(c0 || c1 || c2)
					if(!las) {
						if(F(0, c0 - 1, c1, c2)) {
							las = arr[tot++] = 0;
							--c0;
						} else {
							las = arr[tot++] = 1;
							--c1;
						}
					} else {
						if(F(0, c0, c1 - 1, c2)) {
							las = arr[tot++] = 0;
							--c1;
						} else {
							las = arr[tot++] = 1;
							--c2;
						}
					}
				break;
			}
		for(int i = 0; i < tot; ++i)
			printf("%d", arr[i]);
		puts("");
	}
	return 0;
}