#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int t, n, m, q;
char row[2][maxn], col[2][maxn], pos[maxn << 1 | 1], ans[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%s%s", row[0] + 1, col[0] + 1);
		m = strlen(row[0] + 1);
		n = strlen(col[0] + 1);
		row[1][0] = col[0][1];
		for(int i = 1; i <= m; ++i)
			row[1][i] = row[1][i - 1] == '1' && row[0][i] == '1' ? '0' : '1';
		col[1][0] = row[0][1];
		for(int i = 1; i <= n; ++i)
			col[1][i] = col[1][i - 1] == '1' && col[0][i] == '1' ? '0' : '1';
		char ch = col[1][2];
		for(int i = 2; i <= m; ++i) {
			ch = ch == '1' && row[1][i] == '1' ? '0' : '1';
			pos[2 - i + m] = ch;
		}
		ch = row[1][2];
		for(int i = 2; i <= n; ++i) {
			ch = ch == '1' && col[1][i] == '1' ? '0' : '1';
			pos[i - 2 + m] = ch;
		}
		scanf("%d", &q);
		for(int i = 0; i < q; ++i) {
			int x, y;
			scanf("%d%d", &x, &y);
			if(x == 1) {
				ans[i] = row[1][y];
			} else if(y == 1) {
				ans[i] = col[1][x];
			} else {
				ans[i] = pos[x - y + m];
			}
		}
		ans[q] = '\0';
		puts(ans);
	}
	return 0;
}
