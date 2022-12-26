#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)501, mod = (int)1e9 + 7;
int t, n, cur, pre = 1;
char buf[maxn];
inline void mod_inc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
struct Info {
	int cnt, sum;
	void update(Info const &t, int adt) { // adt <= 2
		mod_inc(cnt, t.cnt);
		mod_inc(sum, t.sum);
		for( ; adt--; mod_inc(sum, t.cnt));
	}
} f[2][2][3];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%s", buf);
		n = strlen(buf);
		memset(f[cur], 0, sizeof f[0]);
		f[cur][0][0] = f[cur][0][2] = f[cur][1][0] = f[cur][1][2] = (Info){1, 0};
		for(int i = 1; i <= n; ++i) {
			int o = buf[n - i] - '0';
			swap(cur, pre);
			memset(f[cur], 0, sizeof f[0]);
			for(int j = 0; j < 2; ++j) {
				int xL = 0, xR = !j ? o : 1;
				for(int k = 0; k < 3; ++k)
					for(int x = xL; x <= xR; ++x) {
						int yL = k & 1 ? x : 0, yR = !k ? x : 1;
						for(int y = yL; y <= yR; ++y) {
							int msk = !k ? 1 | (x > y) << 1 : (k & 1 ? 1 << (1 + (x < y)) : 1 << 2);
							for(int p = 0; p < 3; ++p)
								if((msk >> p) & 1)
									f[cur][j][k].update(f[pre][j | (x < o)][p], x - y + (k > 0));
						}
					}
			}
		}
		printf("%d\n", f[cur][0][0].sum);
	}
	return 0;
}