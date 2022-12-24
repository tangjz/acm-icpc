#include <cstdio>
const int maxn = 301;
int n, m, f[maxn][maxn], g[maxn][maxn];
char buf[maxn];
int main() {
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%s", buf);
		for(int j = 1; j <= m; ++j)
			f[i][j] = buf[j - 1] == '#';
	}
	int lx = 0, ly = 0;
	while(n > 2 && m > 2) {
		int px = 0, py = 0;
		for(int i = 2; i < n && !px; ++i) { // construct g[i][j]
			g[i][2] = f[i - 1][1] ^ g[i - 2][2] ^ g[i - 1][2];
			for(int j = 3; j < m; ++j)
				g[i][j] = f[i - 1][j - 2] ^ f[i - 1][j - 1] ^ g[i - 2][j - 3] ^ g[i - 2][j] ^ g[i - 1][j - 3] ^ g[i - 1][j] ^ g[i][j - 3];
			if((f[i - 1][m - 2] ^ f[i - 1][m - 1] ^ g[i - 2][m - 3] ^ g[i - 1][m - 3] ^ g[i][m - 3])
			|| (f[i - 1][m - 1] ^ f[i - 1][m] ^ g[i - 2][m - 2] ^ g[i - 1][m - 2] ^ g[i][m - 2])) // g[i][m] = g[i][m + 1] = 0
				px = i - 1;
		}
		if(!px) { // g[n][i] = 0
			if(f[n - 1][1] ^ g[n - 2][2] ^ g[n - 1][2])
				px = n - 1;
			for(int i = 3; i < m && !px; ++i)
				if(f[n - 1][i - 2] ^ f[n - 1][i - 1] ^ g[n - 2][i - 3] ^ g[n - 2][i] ^ g[n - 1][i - 3] ^ g[n - 1][i])
					px = n - 1;
			if((f[n - 1][m - 2] ^ f[n - 1][m - 1] ^ g[n - 2][m - 3] ^ g[n - 1][m - 3])
			|| (f[n - 1][m - 1] ^ f[n - 1][m] ^ g[n - 2][m - 2] ^ g[n - 1][m - 2])) // g[n][m] = g[n][m + 1] = 0
				px = n - 1;
		}
		if(!px) { // g[n + 1][i] = 0
			if(f[n][1] ^ g[n - 1][2])
				px = n;
			for(int i = 3; i < m && !px; ++i)
				if(f[n][i - 2] ^ f[n][i - 1] ^ g[n - 1][i - 3] ^ g[n - 1][i])
					px = n;
			if((f[n][m - 2] ^ f[n][m - 1] ^ g[n - 1][m - 3])
			|| (f[n][m - 1] ^ f[n][m] ^ g[n - 1][m - 2])) // g[n + 1][m] = g[n + 1][m + 1] = 0
				px = n;
		}
		if(px) { // bug row detected
			if(lx && ly) { // more than one bug
				f[lx][ly] ^= 1;
				break;
			}
			for(int i = 2; i < m && !py; ++i) { // construct g[j][i]
				g[2][i] = f[1][i - 1] ^ g[2][i - 2] ^ g[2][i - 1];
				for(int j = 3; j < n; ++j)
					g[j][i] = f[j - 2][i - 1] ^ f[j - 1][i - 1] ^ g[j - 3][i - 2] ^ g[j - 3][i - 1] ^ g[j - 3][i] ^ g[j][i - 2] ^ g[j][i - 1];
				if((f[n - 2][i - 1] ^ f[n - 1][i - 1] ^ g[n - 3][i - 2] ^ g[n - 3][i - 1] ^ g[n - 3][i])
				|| (f[n - 1][i - 1] ^ f[n][i - 1] ^ g[n - 2][i - 2] ^ g[n - 2][i - 1] ^ g[n - 2][i])) // g[n][i] = g[n + 1][i] = 0
					py = i - 1;
			}
			if(!py) { // g[i][m] = 0
				if(f[1][m - 1] ^ g[2][m - 2] ^ g[2][m - 1])
					py = m - 1;
				for(int i = 3; i < n && !py; ++i)
					if(f[i - 2][m - 1] ^ f[i - 1][m - 1] ^ g[i - 3][m - 2] ^ g[i - 3][m - 1] ^ g[i][m - 2] ^ g[i][m - 1])
						py = m - 1;
				if((f[n - 2][m - 1] ^ f[n - 1][m - 1] ^ g[n - 3][m - 2] ^ g[n - 3][m - 1])
				|| (f[n - 1][m - 1] ^ f[n][m - 1] ^ g[n - 2][m - 2] ^ g[n - 2][m - 1])) // g[n][m] = g[n + 1][m] = 0
					py = m - 1;
			}
			if(!py) { // g[i][m + 1] = 0
				if(f[1][m] ^ g[2][m - 1])
					py = m;
				for(int i = 3; i < n && !py; ++i)
					if(f[i - 2][m] ^ f[i - 1][m] ^ g[i - 3][m - 1] ^ g[i][m - 1])
						py = m;
				if((f[n - 2][m] ^ f[n - 1][m] ^ g[n - 3][m - 1])
				|| (f[n - 1][m] ^ f[n][m] ^ g[n - 2][m - 1])) // g[n][m + 1] = g[n + 1][m + 1] = 0
					py = m;
			}
			if(py) { // bug detected
				int cnt = 0;
				for(int i = 1; i <= n; ++i)
					for(int j = 1; j <= m; ++j)
						cnt += f[i][j];
				if(cnt == 1) // non-empty
					break;
				lx = px;
				ly = py;
				f[px][py] ^= 1;
				continue;
			}
		}
		lx = ly = 0;
		n -= 2;
		m -= 2;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
				f[i][j] = g[i + 1][j + 1];
	}
	int xL = n, xH = 1, yL = m, yH = 1;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			if(f[i][j]) {
				xL > i && (xL = i);
				xH < i && (xH = i);
				yL > j && (yL = j);
				yH < j && (yH = j);
			}
	for(int i = xL; i <= xH; ++i) {
		for(int j = yL; j <= yH; ++j)
			buf[j - yL] = ".#"[f[i][j]];
		buf[yH - yL + 1] = '\0';
		puts(buf);
	}
	return 0;
}