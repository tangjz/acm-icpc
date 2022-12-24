#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const int maxn = 61;
int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		int m, n, num = 0, den = 1;
		char buf[7];
		scanf("%d%d%s", &m, &n, buf);
		for(int i = 0, o = 0; buf[i]; ++i)
			if(buf[i] == '.') {
				o = 1;
			} else {
				num = num * 10 + (buf[i] - '0');
				if(o)
					den *= 10;
			}
		if(!num || n <= m || m == 1) {
			printf("%.10e\n", !num || n < m ? 0 : (m == 1 ? sin((DB)n * num / den) : pow(sin((DB)num / den), n)));
			continue;
		}
		DB sinX = sin((DB)num / den), cosX = cos((DB)num / den);
		static bool o = 0;
		static DB row[maxn], mat[2][maxn][maxn + 2], *tmp = mat[0][0];
		memset(row + 1, 0, (m + m) * sizeof(DB));
		row[m + 1] = sinX;
		for(int i = 1; i <= m; ++i) {
			memset(mat[o][i] + 1, 0, (m + m) * sizeof(DB));
			memset(mat[o][m + i] + 1, 0, (m + m) * sizeof(DB));
			mat[o][i][m + i] = -1;
			mat[o][m + i][i] = 1;
			mat[o][m + i][m + i] = 2 * cosX;
			mat[o][m + i][m + i + 1] = sinX;
		}
		--n;
		while(1) {
			if(n & 1) {
				memcpy(tmp + 1, row + 1, (m + m) * sizeof(DB));
				memset(row + 1, 0, (m + m) * sizeof(DB));
				for(int i = 1; i <= m + m; ++i)
					for(int j = 1; j <= m + m; ++j)
						row[j] += tmp[i] * mat[o][i][j];
			}
			n >>= 1;
			if(!n)
				break;
			o = !o;
			memset(mat[o][1] + 1, 0, (m + m) * sizeof(DB));
			memset(mat[o][m + 1] + 1, 0, (m + m) * sizeof(DB));
			for(int i = 1; i <= m + m; ++i)
				for(int j = 1; j <= m + m; ++j) {
					mat[o][1][j] += mat[!o][1][i] * mat[!o][i][j];
					mat[o][m + 1][j] += mat[!o][m + 1][i] * mat[!o][i][j];
				}
			for(int i = 2; i <= m; ++i) {
				for(int j = 1; j < i; ++j)
					mat[o][i][j] = mat[o][i][m + j] = mat[o][m + i][j] = mat[o][m + i][m + j] = 0;
				for(int j = i; j <= m; ++j) {
					mat[o][i][j] = mat[o][i - 1][j - 1];
					mat[o][i][m + j] = mat[o][i - 1][m + j - 1];
					mat[o][m + i][j] = mat[o][m + i - 1][j - 1];
					mat[o][m + i][m + j] = mat[o][m + i - 1][m + j - 1];
				}
			}
		}
		printf("%.10e\n", row[m + m]);
	}
	return 0;
}