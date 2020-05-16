#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxr = 51, maxn = 7847, mod = (int)1e9 + 7;
const int maxd = 4, dx[maxd] = {-1, 0, 1, 0}, dy[maxd] = {0, -1, 0, 1};
int n, mat[maxn][maxn];
pair<int, int> coord[maxn];
int mod_inv(int x) {
	int y = mod, u = 1, v = 0;
	while(x) {
		int q = y / x;
		swap(x, y);
		x -= q * y;
		swap(u, v);
		u -= q * v;
	}
	return v < 0 ? v + mod : v;
}
int main() {
	int R, p[4];
	scanf("%d%d%d%d%d", &R, p + 0, p + 1, p + 2, p + 3);
	for(int i = -R; i <= R; ++i)
		for(int j = -R; j <= R; ++j)
			if(i * i + j * j <= R * R)
				coord[n++] = make_pair(i, j);
	int sum = p[0] + p[1] + p[2] + p[3];
	for(int i = 0; i < n; ++i) {
		int px = coord[i].first, py = coord[i].second;
		mat[i][i] = mat[i][n] = sum;
		for(int j = 0; j < maxd; ++j) {
			int cx = px + dx[j], cy = py + dy[j];
			if(cx * cx + cy * cy <= R * R) {
				int pos = lower_bound(coord, coord + n, make_pair(cx, cy)) - coord;
				mat[i][pos] = mod - p[j];
			}
		}
	}
	for(int i = 0; i < n; ++i) {
		int px = coord[i].first, py = coord[i].second;
		int lim = upper_bound(coord + i, coord + n, make_pair(px + 1, py)) - coord;
		int ivs = mod_inv(mat[i][i]);
		for(int j = i + 1; j < lim; ++j) {
			if(!mat[j][i])
				continue;
			int prd = (LL)(mod - mat[j][i]) * ivs % mod;
			for(int k = i; k < lim; ++k)
				mat[j][k] = (mat[j][k] + (LL)prd * mat[i][k]) % mod;
			mat[j][n] = (mat[j][n] + (LL)prd * mat[i][n]) % mod;
		}
	}
	for(int i = n - 1; i >= 0; --i) {
		int val = 0;
		for(int j = i + 1; j < n; ++j)
			if(mat[i][j]) {
				val = (val + (LL)mat[i][j] * mat[j][n]) % mod;
				mat[i][j] = 0;
			}
		mat[i][n] = (LL)(mat[i][n] + mod - val) * mod_inv(mat[i][i]) % mod;
		mat[i][i] = 1;
		int px = coord[i].first, py = coord[i].second;
		if(!px && !py) {
			printf("%d\n", mat[i][n]);
			break;
		}
	}
	return 0;
}