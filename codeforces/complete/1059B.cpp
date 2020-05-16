#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e3 + 1;
int n, m;
char s[maxn][maxn], t[maxn][maxn];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i) {
		scanf("%s", s[i]);
		for(int j = 0; j < m; ++j)
			t[i][j] = '.';
	}
	for(int i = 1; i < n - 1; ++i)
		for(int j = 1; j < m - 1; ++j) {
			bool chk = 1;
			for(int dx = -1; dx <= 1; ++dx)
				for(int dy = -1; dy <= 1; ++dy)
					chk &= !dx && !dy || s[i + dx][j + dy] == '#';
			if(chk)
				for(int dx = -1; dx <= 1; ++dx)
					for(int dy = -1; dy <= 1; ++dy)
						if(dx || dy)
							t[i + dx][j + dy] = '#';
		}
	for(int i = 0; i < n; ++i)
		if(strcmp(s[i], t[i])) {
			puts("NO");
			return 0;
		}
	puts("YES");
	return 0;
}
