#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e3 + 1, mod = (int)1e9 + 7;
int t, n, f[2][3];
char buf[3][maxn];
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d", &n);
		for(int i = 0; i < 3; ++i)
			scanf("%s", buf[i]);
		int cur = 0, pre = 1;
		f[cur][0] = 1;
		f[cur][1] = f[cur][2] = 0;
		for(int i = 0; i < n; ++i) {
			pre ^= 1;
			cur ^= 1;
			f[cur][0] = f[cur][1] = f[cur][2] = 0;
			if(buf[0][i] == '.' && buf[1][i] == '.') {
				(f[cur][0] += f[pre][1]) >= mod && (f[cur][0] -= mod);
				(f[cur][1] += f[pre][0]) >= mod && (f[cur][1] -= mod);
			}
			if(buf[1][i] == '.' && buf[2][i] == '.') {
				(f[cur][1] += f[pre][2]) >= mod && (f[cur][1] -= mod);
				(f[cur][2] += f[pre][1]) >= mod && (f[cur][2] -= mod);
			}
		}
		printf("Case #%d: %d\n", Case, f[cur][2]);
	}
	return 0;
}
