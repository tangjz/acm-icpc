#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
int t, n, a[maxn], p[maxn][2][2];
LL f[maxn][2][2];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		memset(f[0], 0x3f, sizeof f[0]);
		f[0][0][0] = 0;
		for(int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			memset(f[i], 0x3f, sizeof f[0]);
			for(int j = 0; j < 2; ++j)
				for(int k = 0; k < 2; ++k) {
					bool chk0 = 1, chk1 = 1;
					if(i > 1) {
						LL x = j ? -a[i - 1] : a[i - 1];
						chk0 &= a[i] + x > 0;
						chk1 &= -a[i] + x > 0;
						if(i > 2) {
							int y = k ? -a[i - 2] : a[i - 2];
							chk0 &= a[i] + x + y > 0;
							chk1 &= -a[i] + x + y > 0;
						}
					}
					if(chk0) {
						LL tp = f[i - 1][j][k] + a[i];
						if(f[i][0][j] > tp) {
							p[i][0][j] = k;
							f[i][0][j] = tp;
						}
					}
					if(chk1) {
						LL tp = f[i - 1][j][k] - a[i];
						if(f[i][1][j] > tp) {
							p[i][1][j] = k;
							f[i][1][j] = tp;
						}
					}
				}
		}
		int x = n, y = 0, z = 0;
		for(int i = 0; i < 2; ++i)
			for(int j = 0; j < 2; ++j)
				if(f[x][y][z] > f[x][i][j]) {
					y = i;
					z = j;
				}
		while(x > 0) {
			if(y)
				a[x] = -a[x];
			int tp = p[x][y][z];
			--x;
			y = z;
			z = tp;
		}
		for(int i = 1; i <= n; ++i)
			printf("%d%c", a[i], " \n"[i == n]);
	}
	return 0;
}
