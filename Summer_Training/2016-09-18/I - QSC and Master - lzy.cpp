#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define N 300

typedef long long i64;

const i64 inf = 0x3ffffffffffff;

int T, n;
int k[N + 9], v[N + 9];
i64 f[N + 9][N + 9][2];
bool g[N + 9][N + 9];

void upd(i64 &a, i64 b) {
	if (a < b) a = b;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			scanf("%d", k + i);
		for (int i = 1; i <= n; ++i)
			scanf("%d", v + i);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				f[i][j][0] = f[i][j][1] = -inf;
		memset(g, 0, sizeof g);
		for (int i = 1; i <= n; ++i)
			for (int j = i + 1; j <= n; ++j)
				g[i][j] = __gcd(k[i], k[j]) > 1;
		for (int l = n; l >= 1; --l) {
			f[l][l][0] = 0;
			f[l][l - 1][1] = 0;
			for (int r = l + 1; r <= n; ++r) {
				for (int i = l; i < r; ++i) {
					upd(f[l][r][0], f[l][i][0] + f[i + 1][r][0]);
					upd(f[l][r][1], f[l][i][1] + f[i + 1][r][1]);
				}
				if (g[l][r]) {
					upd(f[l][r][0], f[l + 1][r - 1][1] + v[l] + v[r]);
					upd(f[l][r][1], f[l + 1][r - 1][1] + v[l] + v[r]);
				}
			}
		}
		printf("%I64d\n", f[1][n][0]);
	}
	return 0;
}
